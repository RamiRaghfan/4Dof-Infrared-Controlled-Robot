# 4Dof-Infrared-Controlled-Robot
This Arduino program demonstrated a simple way to capture signals from an Infrared remote and use them to control a robot

TO USE: You must find in the pin numbers and adjust according to your wiring, as well as changing all the signal codes for the Infrared controller as they are different for each controller. 

This Arduino program demonstrates how to capture an IR signal and use it to control a servo motor 
Infrared controllers work by sending a very fast encoded sequence of "lights" when sending one command, but when pressing and holding a button a special repeat signal is emittied along with a delay. 

In this program I have attempted to solve this repeating signal and managed to make the servo motors move with a press-and-hold fasion. 


The following model was used for this program.
![b1af87fab3adb48a33630e8655326a39](https://user-images.githubusercontent.com/52379191/170782087-7bfb7705-d147-41f9-a58e-a4a9f394a506.jpg)
