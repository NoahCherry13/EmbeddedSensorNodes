# Embedded Sensor Nodes
## Low Power Embedded Sensor Nodes for Environmental Monitoring
- Part of the Hazard Harbinger Senior Design Project at Boston University
- Robust, low power sensor nodes
- Ad Hoc P2P wireless connection for remote data collection

The embedded sensor node network is a series of distributed nodes composed of a SAMD21 Pro RF microcontroller, sd card interface, and a BME688 multisensor. Nodes enter a low-power sleep state, waking to collect temperature, humidity, pressure, altitude, sulfur organic compounds, and volatile organic compounds, storing it on the SD card, and returning to sleep. When a collector node (connected to the scanning drone) enters into the range of the onboard LoRa antenna, the microcontroller receives an interrupt that wakes the board and transmits all collected data. 

Nodes are estimated to last a year on two AA batteries before requiring service, providing high-resolution, long-term climate data on at-risk regions.
