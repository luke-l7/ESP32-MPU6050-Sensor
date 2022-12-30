# General
In this tutorial, i'm creating a personalized IMU sensor for an academic study, which sends it's samples over the UART
in a specific protocol that i chose, note that this implementation can be changed according to your needs and specifications.

nonetheless, i believe the project provides a great insight as to how send data over the UART.

You'll notice that the fashion that i chose to transmit the live IMU samples is bigEndian, i'll make sure to point that out
in the specific functions.

# Hardware
- Raspberry PI 4B
- [NodeMCU-32S module](https://www.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B081CSJV2V/ref=sr_1_1_sspa?crid=1O40H1IT35KNV&keywords=NodeMCU-32S+module&qid=1666180772&qu=eyJxc2MiOiIxLjk1IiwicXNhIjoiMC4wMCIsInFzcCI6IjAuMDAifQ%3D%3D&sprefix=mpu+6050%2Caps%2C708&sr=8-1-spons&psc=1)
- [MPU-6050 sensor module](https://www.amazon.com/GalaxyElec-MPU-6050-MPU6050-sensors-Accelerometer/dp/B082HTG558/ref=sr_1_2?crid=25MVDU2UEUCRO&keywords=MPU+6050&qid=1666180592&qu=eyJxc2MiOiIyLjc3IiwicXNhIjoiMi45NSIsInFzcCI6IjIuODQifQ%3D%3D&sprefix=mpu+6050%2Caps%2C269&sr=8-2)
- Cables (ofcourse)

## Connections

<img src="/ESP32-MPU6050-Sensor/assets/employee.png" alt="Employee data" title="Employee Data title">
