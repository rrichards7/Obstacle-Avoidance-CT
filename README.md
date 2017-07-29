![image001](https://user-images.githubusercontent.com/23239868/28748600-b190782c-7489-11e7-82ae-55db54c94050.jpg)
# Autonomous Snowmobile Monocular Obstacle Avoidance
*Lead Architect: Ryan J. Richards*

*LabVIEW and OpenCV code for obstacle detection and avoidance in snowy conditions*

![ezgif com-video-to-gif 4](https://user-images.githubusercontent.com/23239868/28676573-ff21a2be-72b8-11e7-88fa-b2b459883bd7.gif)

## Methodology ##

Autonomous vehicles in snowy environments require an obstacle avoidance feature. Rather than using expensive equipment (LIDAR, sonar, etc),  a simple monocular solution can be created. This single-camera setup uses simple thresholding and particle analysis techniques to detect and highlight any obstacles. After detection, a steering avoidance script can be written to bypass the obstacle based on its location.

Although Optical-Flow based methods have been asserted in the past for monocular obstacle avoidance, a better algorithm involves color threshold and particle analysis - which takes advantage of the snow-covered environment. A feedforward image processing system has been created that has the following architecture:

![untitled diagram](https://user-images.githubusercontent.com/23239868/28692853-61054774-72f0-11e7-9c6b-1f76897dc23a.jpg)

## LabVIEW Code ##

LabVIEW IMAQ (image acquisition) libraries [1] have been used extensively to complete the feedforward system. 

![1](https://user-images.githubusercontent.com/23239868/28693449-b45ea2ec-72f2-11e7-9ce3-2f288aeb96af.PNG)


## OpenCV/C++ Code ##

## OpenCV/Python Code ##

## RaspberryPi/GoPro Integration ##

## Testing/Results ##

![ezgif com-video-to-gif 2](https://user-images.githubusercontent.com/23239868/28652591-a7a80e5e-7256-11e7-9c03-d41bdddb1ac8.gif)

![ezgif com-video-to-gif 6](https://user-images.githubusercontent.com/23239868/28677336-38f9dc2a-72bb-11e7-8e94-b41546a17c08.gif)


## Appendix ##

[1] http://www.ni.com/white-paper/3470/en/
