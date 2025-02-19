from aiocoap import resource, Context, Message
import asyncio

class SensorResource(resource.Resource):
    async def render_post(self, request):
        payload = request.payload.decode()
        # Add to InfluxDB queue
        process_data.delay(payload)
        return Message(code=coap.CHANGED)

async def main():
    root = resource.Site()
    root.add_resource(('sensor',), SensorResource())
    await Context.create_server_context(root)
    await asyncio.get_event_loop().create_future()

if __name__ == "__main__":
    asyncio.run(main())
