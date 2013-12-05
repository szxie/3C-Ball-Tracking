3C科创 by clz
===============
### AIM：

* 算出图中圆的直径
* 直径->摄像头距离->（x,y）坐标
* 图->视频

### Code (in ./code)

* 3C.cpp

主函数，摄像头输入

* 3CC.cpp

主函数，处理一张图片

* EdgeF.cpp

边缘函数，输入原图，返回边缘图

* HSVF.cpp

HSV函数，输入原图和边缘图，返回HSV后的边缘图

* CircleF.cpp

找圆函数，输入HSV边缘图和原图，返回加上找到的圆的图

### Data (in ./data)
* all tx_1.jpg 都为1366*768 或 1366*908
* t5_1.jpg 和 t6_1.jpg 的区别在于照相时对焦点是否在球上

### TO DO
* 准确度问题
主要是边缘的效果不好

* 代码结构
可能会崩溃，希望能统一为C++格式

### Other
[OpenCV手册][ref]
[ref]: http://www.opencv.org.cn/opencvdoc/2.3.2/html/index.html

