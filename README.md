# Delt-Lighting
Source code for Arduino to control the basement lights
    - Please look at the file structure I made for the Rainbow feature and copy based off of that
        - Put my implementation all in a .h file - feel free to split it up between a .h and .cpp. Just did this for the sake of time.
        - The Lights.ino file is a C++ file with a wrapper so that the arduino can run it

Ignore the error when you import FastLED.h into your file - it's fixed when running on the Arduino (hopefully)
    - If not I'll figure out how to take care of that missing interrupt file