# BinAlert: Real-Time Garbage Collection Notification System

## Project Overview
The BinAlert project aims to enhance waste management efficiency by providing real-time notifications to facility managers when garbage bins are emptied. Utilizing accelerometer sensors coupled with embedded TinyML models, the system can accurately detect and report the status of garbage bin collection, facilitating optimal operational management across multiple facilities.

## Features
- **Real-time Notifications:** Instant alerts to facility managers upon garbage bin emptying.
- **Accuracy in Detection:** High accuracy in detecting tilt movements of bins using accelerometer sensors.
- **Integration:** Seamless integration into existing waste management protocols without disruption.
- **Sustainability:** Promotes efficient and sustainable urban waste management practices.

## Technology Stack
- **Sensors:** MPU6050 accelerometer for motion detection.
- **Microcontroller:** Raspberry Pi Pico with RP2040 chip, running TinyML models.
- **Software:** Edge Impulse for developing and deploying machine learning models.
- **Communication:** NodeMCU for IoT connectivity and notifications via Arduino Cloud IoT service.

## Getting Started
### Prerequisites
- Raspberry Pi Pico with RP2040
- MPU6050 accelerometer sensor
- NodeMCU board
- Basic electronic components (wires, breadboard, etc.)
- Arduino IDE

### Installation
1. **Set up the hardware:** Connect the MPU6050 accelerometer to the Raspberry Pi Pico according to the circuit diagrams provided in the `diagrams` folder.
2. **Flash the microcontroller:** Upload the Pico firmware from the `firmware` folder using the Arduino IDE.
3. **Configure NodeMCU:** Set up the NodeMCU board to connect to your Wi-Fi network and link it with the Arduino Cloud IoT service.
4. **Assembly:** Secure all components in a suitable enclosure to ensure durability and operational integrity.

## Usage
Once the system is powered and all components are correctly configured, it will automatically begin monitoring the tilt activities of the attached garbage bin. Notifications are sent in real-time when the bin is detected to be emptied.


## Acknowledgements
- Prof. Dr. Oliver Amft and Mr. Mohammed Bourouah for their invaluable guidance and supervision.
- The Edge Impulse team for providing the tools and support needed for TinyML development.

## Demo
- Project DEmo can be viewed through the link: https://drive.google.com/file/d/1sdM3bjLtpO-aVOasQOG5pRu-Pzt8wuOh/view?usp=sharing

Feel free to reach out for any queries or collaboration opportunities.
