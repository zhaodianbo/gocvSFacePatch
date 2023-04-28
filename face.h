#ifndef _OPENCV3_FACE_H_
#define _OPENCV3_FACE_H_

#ifdef __cplusplus
#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
extern "C" {
#endif

#include "core.h"

#ifdef __cplusplus
typedef cv::Ptr<cv::FaceDetectorYN>* FaceDetectorYN;
typedef cv::Ptr<cv::FaceRecognizerSF>* FaceRecognizerSF;
typedef cv::Mat* Mat;
#else
typedef void* FaceDetectorYN;
typedef void* FaceRecognizerSF;
typedef void* Mat;
#endif

/*typedef struct Size {
int width;
int height;
} Size;
typedef struct ByteArray {
char* data;
int length;
} ByteArray;*/

//void MyMat_Close(Mat m);
//Mat MyMat_New();
//Mat MyMat_NewFromBytes(int rows, int cols, int type, struct ByteArray buf);
FaceDetectorYN FaceDetectorYN_create(const char* model, const char* config,
const Size input_size,
float score_threshold ,
float nms_threshold ,
int top_k ,
int backend_id ,
int target_id );

void FaceDetectorYN_setInputSize(FaceDetectorYN d,const Size input_size);
Size FaceDetectorYN_getInputSize(FaceDetectorYN d) ;
void FaceDetectorYN_setScoreThreshold(FaceDetectorYN d,float score_threshold) ;
float FaceDetectorYN_getScoreThreshold(FaceDetectorYN d) ;
void FaceDetectorYN_setNMSThreshold(FaceDetectorYN d,float nms_threshold) ;
float FaceDetectorYN_getNMSThreshold(FaceDetectorYN d) ;
void FaceDetectorYN_setTopK(FaceDetectorYN d,int top_k) ;
int FaceDetectorYN_getTopK(FaceDetectorYN d) ;
int FaceDetectorYN_detect(FaceDetectorYN d,Mat image, Mat faces);
void FaceDetectorYN_delete(FaceDetectorYN f);

FaceRecognizerSF FaceRecognizerSF_create(const char* model, const char* config, int backend_id , int target_id);
void FaceRecognizerSF_alignCrop(FaceRecognizerSF d,Mat src_img, Mat face_box, Mat aligned_img) ;
void FaceRecognizerSF_feature(FaceRecognizerSF d,Mat aligned_img, Mat face_feature);
double FaceRecognizerSF_match(FaceRecognizerSF d,Mat face_feature1, Mat face_feature2, int dis_type ) ;
void FaceRecognizerSF_delete(FaceRecognizerSF d);

double SFace_Test(const char* dmodel,const char* rmodel,Mat img1, Mat img2);

#ifdef __cplusplus
}
#endif
#endif