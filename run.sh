#!/bin/sh

PROCESS=`docker ps | grep esp-open-rtos`
if [ "$PROCESS" != "" ]; then
	docker exec -it esp-open-rtos bash
else
	docker-compose up -d 
	docker exec -it esp-open-rtos bash
fi


