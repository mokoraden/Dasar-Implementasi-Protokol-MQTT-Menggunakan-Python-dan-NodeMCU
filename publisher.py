
import paho.mqtt.client as paho
import time

def on_publish(client, userdata, mid):
      print("mid: "+str(mid))
client = paho.Client()
client.on_publish = on_publish
client.username_pw_set("ylfxubjy", "Bo3U7GcN5NAF")
client.connect("postman.cloudmqtt.com", 14843, 60)
client.loop_start()

while True:
      teksdikirim="Selamat Pagi"
      client.publish("/percobaan", str(teksdikirim), qos=1)
      time.sleep(1)