3C科创 by clz
===============
### AIM：

* 算出图中圆的直径
* 直径->摄像头距离->（x,y）坐标
* 图->视频

### Code (in ./code)

* main.cpp

主函数，摄像头输入

* main2.cpp

主函数，处理一张图片

* Edge.cpp

边缘函数，两个参数，原图，结果图

* HSV.cpp

HSV函数，三个参数，原图，边缘图，结果图 （计算依赖，结果依赖，结果）

* Circle.cpp

找圆函数，三个参数，边缘图，原图，结果图 （计算依赖，结果依赖，结果）

### Data (in ./data)
* all tx_1.jpg 都为1366*768 或 1366*908
* t5_1.jpg 和 t6_1.jpg 的区别在于照相是否对焦在球上

### TO DO
* 准确度问题

主要是边缘的效果不好

* 用视频记录下目前结果

* 对环境调节严重依赖，换球的颜色

* 如何取优解

### Other
[OpenCV手册][ref]
[ref]: http://www.opencv.org.cn/opencvdoc/2.3.2/html/index.html

[Color Detection & Object Tracking][ref]
[ref]: http://opencv-srf.blogspot.com/2010/09/object-detection-using-color-seperation.html

> There is a open source software, called 'ColorWheelHSV', that enables you to find the 'hue', 'saturation' and 'value' for a specific object easily.
