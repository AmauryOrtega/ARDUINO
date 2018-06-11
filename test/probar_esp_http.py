import requests, time, pprint
DEBUG = False

IP_ESP8266 = "192.168.0.111"
ZONAS = ['13', '12', '16']
SEG_ENTRE_ZONAS = 0

# Encendiendo zonas
for PIN in ZONAS:
    print("Encendiendo Zona " + PIN)
    r = requests.get("http://" + IP_ESP8266 + "/digital/" + PIN + "/1")
    print(r.json()["message"])
    if DEBUG:
        pprint.pprint(r.json())
    time.sleep(SEG_ENTRE_ZONAS)

# Apagando zonas
for PIN in ZONAS:
    print("Apagando Zona " + PIN)
    r = requests.get("http://" + IP_ESP8266 + "/digital/" + PIN + "/0")
    print(r.json()["message"])
    if DEBUG:
        pprint.pprint(r.json())
    time.sleep(SEG_ENTRE_ZONAS)
