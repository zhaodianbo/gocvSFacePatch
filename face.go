package gocv

/*
//#cgo !windows pkg-config: opencv4
//#cgo CXXFLAGS:   --std=c++11
#include <stdlib.h>
#include "face.h"
*/
import "C"
import (
	"image"
	"unsafe"
)

type FaceDetectorYN struct {
	p unsafe.Pointer
}

type FaceRecognizerSF struct {
	p unsafe.Pointer
}

func NewFaceDetectorYN(model, config string, inputSize image.Point, scoreThreshold, nmsThreshold float32, topK, backendID, targetID int) FaceDetectorYN {
	cModel := C.CString(model)
	defer C.free(unsafe.Pointer(cModel))
	cConfig := C.CString(config)
	defer C.free(unsafe.Pointer(cConfig))
	sz := C.struct_Size{
		width:  C.int(inputSize.X),
		height: C.int(inputSize.Y),
	}

	f := C.FaceDetectorYN_create(cModel, cConfig, sz, C.float(scoreThreshold), C.float(nmsThreshold), C.int(topK), C.int(backendID), C.int(targetID))

	return FaceDetectorYN{p: unsafe.Pointer(f)}
}
func (fd *FaceDetectorYN) CloseFaceDetectorYN() {
	C.FaceDetectorYN_delete((C.FaceDetectorYN)(fd.p))
}

func (fd *FaceDetectorYN) SetInputSize(inputSize image.Point) {
	sz := C.struct_Size{
		width:  C.int(inputSize.X),
		height: C.int(inputSize.Y),
	}
	C.FaceDetectorYN_setInputSize((C.FaceDetectorYN)(fd.p), sz)
}

func (fd *FaceDetectorYN) GetInputSize() C.Size {
	return C.FaceDetectorYN_getInputSize((C.FaceDetectorYN)(fd.p))
}

func (fd *FaceDetectorYN) SetScoreThreshold(scoreThreshold float32) {
	C.FaceDetectorYN_setScoreThreshold((C.FaceDetectorYN)(fd.p), C.float(scoreThreshold))
}

func (fd *FaceDetectorYN) GetScoreThreshold() float32 {
	return float32(C.FaceDetectorYN_getScoreThreshold((C.FaceDetectorYN)(fd.p)))
}

func (fd *FaceDetectorYN) SetNMSThreshold(nmsThreshold float32) {
	C.FaceDetectorYN_setNMSThreshold((C.FaceDetectorYN)(fd.p), C.float(nmsThreshold))
}

func (fd *FaceDetectorYN) GetNMSThreshold() float32 {
	return float32(C.FaceDetectorYN_getNMSThreshold((C.FaceDetectorYN)(fd.p)))
}

func (fd *FaceDetectorYN) SetTopK(topK int) {
	C.FaceDetectorYN_setTopK((C.FaceDetectorYN)(fd.p), C.int(topK))
}

func (fd *FaceDetectorYN) GetTopK() int {
	return int(C.FaceDetectorYN_getTopK((C.FaceDetectorYN)(fd.p)))
}

func (fd *FaceDetectorYN) Detect(image Mat, faces *Mat) int {

	return int(C.FaceDetectorYN_detect((C.FaceDetectorYN)(fd.p), image.p, faces.p))
}

func NewFaceRecognizerSF(model, config string, backendID, targetID int) FaceRecognizerSF {
	cModel := C.CString(model)
	defer C.free(unsafe.Pointer(cModel))
	cConfig := C.CString(config)
	defer C.free(unsafe.Pointer(cConfig))

	f := C.FaceRecognizerSF_create(cModel, cConfig, C.int(backendID), C.int(targetID))

	return FaceRecognizerSF{p: unsafe.Pointer(f)}
}

type DisType int

const (
	FR_COSINE DisType = iota
	FR_NORM_L2
)

func (fr *FaceRecognizerSF) AlignCrop(srcImg, faceBox Mat, alignedImg *Mat) {
	C.FaceRecognizerSF_alignCrop((C.FaceRecognizerSF)(fr.p), srcImg.p, faceBox.p, alignedImg.p)
}

func (fr *FaceRecognizerSF) Feature(alignedImg Mat, faceFeature *Mat) {
	C.FaceRecognizerSF_feature((C.FaceRecognizerSF)(fr.p), alignedImg.p, faceFeature.p)
}

func (fr *FaceRecognizerSF) Match(faceFeature1, faceFeature2 Mat, disType DisType) float64 {
	return float64(C.FaceRecognizerSF_match((C.FaceRecognizerSF)(fr.p), faceFeature1.p, faceFeature2.p, C.int(disType)))
}

func (fr *FaceRecognizerSF) CloseFaceRecognizerSF() error {
	C.FaceRecognizerSF_delete((C.FaceRecognizerSF)(fr.p))
	return nil
}

func SFace_Test(detect_model,recog_model string,  img1,  img2 Mat) float64 {
	cModel := C.CString(detect_model)
	defer C.free(unsafe.Pointer(cModel))
	rModel := C.CString(recog_model)
	defer C.free(unsafe.Pointer(rModel))
	return float64(C.SFace_Test(cModel,rModel, img1.p,  img2.p))
}