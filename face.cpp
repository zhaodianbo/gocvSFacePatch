#include "face.h"

FaceDetectorYN FaceDetectorYN_create(const char* model, const char* config,
                                      const Size input_size,
                                      float score_threshold,
                                      float nms_threshold,
                                      int top_k,
                                      int backend_id,
                                      int target_id)
{
    cv::Size sz(input_size.width, input_size.height);

    return new cv::Ptr<cv::FaceDetectorYN>(cv::FaceDetectorYN::create(model, config, sz, score_threshold, nms_threshold, top_k, backend_id, target_id));
}
void FaceDetectorYN_delete(FaceDetectorYN f){
    delete f;
}
void FaceDetectorYN_setInputSize(FaceDetectorYN fd,const Size input_size)
{
    cv::Size sz(input_size.width, input_size.height);
    (*fd)->setInputSize(sz);
}

Size FaceDetectorYN_getInputSize(FaceDetectorYN fd)
{
     cv::Size sz=(*fd)->getInputSize();
    Size s=Size{sz.width,sz.height};
    return s;
}

void FaceDetectorYN_setScoreThreshold(FaceDetectorYN fd,float score_threshold)
{
    (*fd)->setScoreThreshold(score_threshold);
}

float FaceDetectorYN_getScoreThreshold(FaceDetectorYN fd)
{
    return (*fd)->getScoreThreshold();
}

void FaceDetectorYN_setNMSThreshold(FaceDetectorYN fd,float nms_threshold)
{
    (*fd)->setNMSThreshold(nms_threshold);
}

float FaceDetectorYN_getNMSThreshold(FaceDetectorYN fd)
{
    return (*fd)->getNMSThreshold();
}

void FaceDetectorYN_setTopK(FaceDetectorYN fd,int top_k)
{
    (*fd)->setTopK(top_k);
}

int FaceDetectorYN_getTopK(FaceDetectorYN fd)
{
    return (*fd)->getTopK();
}

int FaceDetectorYN_detect(FaceDetectorYN fd,Mat image, Mat faces)
{
    return (*fd)->detect(*image, *faces);
}

FaceRecognizerSF FaceRecognizerSF_create(const char* model, const char* config, int backend_id, int target_id)
{
    return new cv::Ptr<cv::FaceRecognizerSF>(cv::FaceRecognizerSF::create(model, config, backend_id, target_id));
}

void FaceRecognizerSF_alignCrop(FaceRecognizerSF fr,Mat src_img, Mat face_box, Mat aligned_img)
{
    (*fr)->alignCrop(*src_img, *face_box, *aligned_img);
}

void FaceRecognizerSF_feature(FaceRecognizerSF fr,Mat aligned_img, Mat face_feature)
{
    (*fr)->feature(*aligned_img, *face_feature);
}

double FaceRecognizerSF_match(FaceRecognizerSF fr,Mat face_feature1, Mat face_feature2, int dis_type)
{
    return (*fr)->match(*face_feature1, *face_feature2, dis_type);
}
void FaceRecognizerSF_delete(FaceRecognizerSF d){
    delete d;
}

double SFace_Test(const char* detect_model,const char* recog_model,Mat img1, Mat img2){

    cv::Ptr<cv::FaceDetectorYN> faceDetector = cv::FaceDetectorYN::create(detect_model, "", cv::Size(150, 150));
    cv::Ptr<cv::FaceRecognizerSF> faceRecognizer = cv::FaceRecognizerSF::create(recog_model, "");

    faceDetector->setInputSize(img1->size());
    cv::Mat faces;
    faceDetector->detect(*img1, faces);
    cv::Mat aligned_face;
    faceRecognizer->alignCrop(*img1, faces.row(0), aligned_face);
    cv::Mat feature;
    faceRecognizer->feature(aligned_face, feature);
    // save feature
    cv::Mat feature1=feature.clone();

    faceDetector->setInputSize(img2->size());
    cv::Mat faces2;
    faceDetector->detect(*img2, faces2);
    cv::Mat aligned_face2;
    faceRecognizer->alignCrop(*img2, faces2.row(0), aligned_face2);
    cv::Mat feature2;
    faceRecognizer->feature(aligned_face2, feature2);

    double ret= faceRecognizer->match(feature1, feature2, cv::FaceRecognizerSF::DisType::FR_COSINE);
    printf("ret=%.4lf\n",ret);
    return ret;

}