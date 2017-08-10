Que se puede hacer con docker file
* Montar en /etc/mosquitto/conf.d/ archivos .conf de configuracion local

apk update & apk add mosquitto mosquitto-clients
expose 1883
entrypoint o cmd "mosquitto" 'Falta parametro para usar la configuracion'
