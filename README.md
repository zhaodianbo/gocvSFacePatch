## GoCV 补丁: 实现 SFace 接口调用
## GoCV Patch: Implementing SFace Interface

这是一个 GoCV 的补丁，用于实现 [SFace](https://github.com/opencv/opencv/blob/4.x/modules/objdetect/src/face_detect.cpp) 接口的调用。SFace 是一个人脸识别算法库，可以用于识别和验证人脸。

该补丁包含了 SFace 接口的实现，你可以使用它来集成 SFace 到你的 GoCV 应用中。使用该补丁，你可以轻松地进行人脸检测、人脸识别和人脸验证。

如果你想要使用 SFace，可以通过该补丁来实现。它提供了一种简单、快速、可靠的方式来集成 SFace 到你的应用中。

### 安装方法
首先，请确保你已经安装了 GoCV 和 Opencv（>4.7.0）。
下载补丁文件并将其添加到你的 GoCV 包中。
在你的应用程序中导入补丁包并使用其中的接口。
使用方法
该补丁提供了以下接口：

* Detect：用于检测人脸。
* Feature：用于提取人脸特征。
* Match：用于验证人脸。

### 测试代码：

    func main() {
        img1 := gocv.IMRead("./img/1.jpg", gocv.IMReadColor)
        defer img1.Close()
        img2 := gocv.IMRead("./img/2.jpg", gocv.IMReadColor)
        defer img2.Close()
        cosineScore :=  gocv.SFace_Test("./face_detection_yunet_2022mar.onnx","./face_recognition_sface_2021dec.onnx" ,img1, img2 ) 
        fmt.Printf("res=%.4f\n ", cosineScore)
    }
### 贡献
如果你发现了任何问题或有任何建议，请随时向我们发送 Pull Request 或 Issue。我们非常欢迎你的贡献！

### 许可证
该补丁遵循 Apache 许可证 2.0。请参阅 LICENSE 文件以获取更多详细信息。

### 参考
[face_recognition_sface](https://github.com/opencv/opencv_zoo/tree/master/models/face_recognition_sface)
