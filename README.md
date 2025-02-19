# Artemis
Unikernel-based Distributed Sensor Network 
## Overview

This project implements a **Unikernel-based Distributed Sensor Network** using **ESP32, CoAP, Flask, Raft, InfluxDB, Celery, and Redis**. It enables efficient, secure, and scalable data acquisition from multiple sensor nodes.

## Features

- **ESP32 Sensor Nodes**: Collects telemetry data (temperature, humidity) and sends it via **CoAP**.
- **CoAP Messaging Framework**: Ensures lightweight and efficient communication between nodes and the server.
- **Flask Backend with InfluxDB**: Receives sensor data and stores it in a time-series database for analysis.
- **Raft Consensus**: Implements leader election and fault tolerance for distributed nodes.
- **Celery + Redis**: Handles asynchronous task processing for real-time data ingestion.
- **Grafana Dashboard**: Visualizes sensor data in real time.

## Tech Stack

- **Firmware**: MicroPython (ESP32)
- **Networking**: CoAP (aiocoap)
- **Backend**: Flask, InfluxDB
- **Distributed Consensus**: Raft (pymrRaft)
- **Task Queue**: Celery + Redis
- **Visualization**: Grafana

## Installation

### Prerequisites

- Python 3.8+
- Redis
- InfluxDB 2.x
- Flask
- aiocoap
- Celery
- Grafana (optional, for visualization)

### Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/unikernel-sensor-network.git
   cd unikernel-sensor-network
   ```
2. Install dependencies:
   ```bash
   pip install -r requirements.txt
   ```
3. Start Redis server:
   ```bash
   redis-server
   ```
4. Run Flask API server:
   ```bash
   python server.py
   ```
5. Start Celery worker:
   ```bash
   celery -A server.celery worker --loglevel=info
   ```

## Usage

### Running ESP32 Client (Simulated in Python)

```bash
python esp32_client.py
```

### Accessing Data

- Sensor data is stored in **InfluxDB** and can be queried using the InfluxDB UI.
- Use **Grafana** to visualize real-time sensor readings.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

[MIT License](LICENSE)

