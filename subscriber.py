

import paho.mqtt.client as paho

def on_subscribe(client, userdata, mid, granted_qos):
      print("Subscribed: "+str(mid)+" "+str(granted_qos))

def on_message(client, userdata, msg):
      print(str(msg.payload))

client=paho.Client()
client.on_subscribe=on_subscribe
client.on_message = on_message
client.username_pw_set("ylfxubjy", "Bo3U7GcN5NAF") #Isikan username Password disini
client.connect("postman.cloudmqtt.com",14843, 60) #Isikan 
#alamat Server/VPS yang dijadikan MQTT Server
client.subscribe("/percobaan", qos=1) #Isikan alamat topik 
#yang dituju (/percobaan) dengan qos= 1
client.loop_forever()