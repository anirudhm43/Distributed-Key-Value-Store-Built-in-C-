#!/bin/bash

CLIENTS=10
REQUESTS=100

for ((i=1;i<=CLIENTS;i++))
do
(
    for ((j=1;j<=REQUESTS;j++))
    do
        {
            echo "PUT user${i}_${j} value${j}"
            sleep 0.01
        } | nc localhost 8080 > /dev/null
    done
)&
done

wait

echo "Load test completed."
