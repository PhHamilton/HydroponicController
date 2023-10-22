HOSTNAME=pi
IP=192.168.1.175
LOCATION=/home/pi/HydroponicController
FLAGS=-r

scp ${FLAGS} Makefile inc src ${HOSTNAME}@${IP}:${LOCATION}
