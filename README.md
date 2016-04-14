# Vex_Swerve

Code Created by khungryapple from [Robodox 599](https://github.com/Robodox-599)

## How it works:

![image of joystick](https://github.com/khungryapple/Vex_Swerve/blob/master/Untitled.png)
- The joystick coordinate would represent x and y value of the imaginary graph
- The code will calculate the hypotenuse using pythagorean theorem
- The value of hypotenuse will represent the speed of the drive
- Using trig function, the code will compute the angle of the joystick - starting from conventional 0 degree mark
- The wheel will turn to corresponding angle, and that is how it works :D
- I am fully aware that square root used in pythagorean theorem will cause you to calculate only up to 180 degrees, and I found a way to prevent that from happening
- (0,0), (1,0), (0,1), (-1,0), (0,-1) will cause autonmatic 0 regardless of other value. So, I had to use both sin and cos to prevent from that to happen
- __There are comments in the code!__ Please check it out first before asking me a question :)
