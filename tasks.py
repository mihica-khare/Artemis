from celery import Celery
from influxdb import InfluxDBClient

app = Celery('tasks', broker='redis://localhost:6379/0')

@app.task
def process_data(payload):
    client = InfluxDBClient(host='localhost', port=8086)
    client.write_points([{
        "measurement": "temperature",
        "fields": {"value": float(payload.split('=')[1])}
    }])
