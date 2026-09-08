I built a dummy stabilization software that uses LED brightness to act as motor strength. It is an MPU 6050 as the sensor and an ESP32 as the microcontroller.

For this project, I wanted to use an ESP32 and an MPU-6050 to build a flight controller like build, the reason being that flight controllers are usually more expensive and the components that you need to build an FPV drone would be too expensive for my current state.

I bought the initial microcontroller and the MPU-6050 to start building the software and the dummy drone just to test if it would work. I built the code using Gemini and edited it myself.

For the dummy drone build, I used red and blue LEDs to simulate having clockwise and counter-clockwise motors and used resistors and jumper wires to connect them to the ESP32. I attached pictures and a video to show the wiring and the way it worked out to be.

I also set up control commands using WASD to move forward, backward, left, and right, along with the arrow keys to handle upward, downward, and rotational movements. The controls are a bit rough around the edges since they do not automatically snap back to zero yet, though I did program the spacebar as a manual zero mechanism. I will likely refine these software controls later, and I am planning to transition to physical potentiometers and joystick controllers down the line, but this covers it for now.

I'm going to admit the software isn't that impressive, it still needs some editing, but this is only version one of the project and I'm going to be posting about V2, V3, etc. till I finish the project on this GitHub post.
<img width="1000" height="750" alt="4" src="https://github.com/user-attachments/assets/28a85c04-f5ec-42e3-aa22-259ce323e338" />
<img width="1000" height="750" alt="3" src="https://github.com/user-attachments/assets/b532c15d-3dc0-4173-ac36-d1d43f582dd1" />
<img width="1000" height="750" alt="2" src="https://github.com/user-attachments/assets/250f676f-e96e-4200-bdd6-eaee555b692c" />
<img width="1000" height="750" alt="1" src="https://github.com/user-attachments/assets/820f3ba3-5254-4485-a2ce-892649b8d31c" />
