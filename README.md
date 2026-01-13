# GPRS-Vehicle-Accident-Alert-System  🚑
Description

The Smart Ambulance Accident Detection and Rescue Alert System is an IoT-based solution designed to improve emergency medical transportation safety. This system automatically detects ambulance accidents using sensors like the ADXL335 accelerometer and SW-420 vibration sensor, tracks the vehicle’s location with the NEO-6M GPS module, and sends real-time alerts through the SIM800L GSM module. Additionally, it monitors driver sobriety using an MQ-3 alcohol sensor.

The project integrates multiple hardware components including Arduino Mega, 9V batteries, HC-05 Bluetooth, 16x2 LCD, and gear motors, aiming to reduce response times and prevent fatalities in road accidents. This system is particularly suited for high-risk environments such as busy roads in Sri Lanka.

Challenges & Questions Encountered

During the development of this project, several practical challenges arose:

1. Component Connectivity Issues: While connecting components, the system often failed to respond, even when wiring appeared correct.

  <img width="1600" height="1200" alt="image" src="https://github.com/user-attachments/assets/f4a261e8-f1bb-414a-bb7c-ffcc113e9439" />


2. Board Limitations: The project could not run entirely on a single Arduino Uno. Adding a Mega board increased system complexity.

   <img width="1280" height="960" alt="image" src="https://github.com/user-attachments/assets/5f3e838b-c550-43ca-b6db-fe39bb4fc4db" />


3. Power Supply Knowledge Gap: Determining the required voltage and current for all components consumed a lot of time due to limited prior experience with power calculations.

   <img width="1280" height="960" alt="image" src="https://github.com/user-attachments/assets/3b6a105e-1e21-4fbc-b4c8-d3d14ff4d677" />


4. LCD Display Considerations: Initially, a 12C LCD display with more pins caused delayed signals due to excessive wiring. Choosing a 4-pin version or using connectors helped, but added extra components.

   <img width="1280" height="960" alt="image" src="https://github.com/user-attachments/assets/d0f0bf6b-6b85-41a6-a454-f9963f5b89d1" />


8. Module Integration Complexity: Coordinating vibration sensors, GPS, GSM, and other modules to work together reliably required multiple iterations of debugging.

   <img width="1280" height="960" alt="image" src="https://github.com/user-attachments/assets/2b7bfa9d-adf2-47b3-bbec-7a7bd6a6bcf5" />

   <img width="1280" height="960" alt="image" src="https://github.com/user-attachments/assets/7ca9d384-0d4a-461d-b14b-fab01e5d0890" />



💡 Lesson Learned: When attempting a project like this, avoid these mistakes by planning your component connections, verifying power requirements early, selecting compatible modules, and keeping wiring neat and minimal wherever possible.


