3C科创 by clzl
===============
### AIM：

* 算出图中圆的直径
* 直径->摄像头距离->（x,y）坐标
* 图->视频
* 定量分析

### Architecture

* 两种找圆方法：霍夫圆和HSV数据分析

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

* adujstHSV.cpp

用来调整HSV阀值

### Data (in ./data)
* all tx_1.jpg 都为1366*768 或 1366*908
* t5_1.jpg 和 t6_1.jpg 的区别在于照相是否对焦在球上

### TO DO
* 提高运动时的精度

* 评估得到的直径结果质量

* 对环境调节严重依赖，换球的颜色，使用前校准

* 如何取优解，直径结果平均处理

* 小球和摄像头之间的最大允许距离

* 测试利用直径计算球和摄像头距离的可行性

* 准备小球和摄像头

* 多摄像头结果，坐标计算

* 实际环境调试

### Other
[OpenCV手册][ref]
[ref]: http://www.opencv.org.cn/opencvdoc/2.3.2/html/index.html#

> There is a open source software, called 'ColorWheelHSV', that enables you to find the 'hue', 'saturation' and 'value' for a specific object easily.
