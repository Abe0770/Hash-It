#!/bin/bash
# HashIt version v1.00

trap 'printf "\n"; exit' 2

printf "HashIt Ver 1.00 \n\n"

if [ "$EUID" -ne 0 ]; then 
    echo "Root permissions required"
    exit 1
fi

make
if [ $? -ne 0 ]; then
    echo "Make failed."
    exit 1
fi

FILE=getHash

if [ -f "$FILE" ]; then
    chmod +x "$FILE"
    sudo cp "$FILE" /usr/local/bin/getHash
    printf "\nSuccessfully installed HashIt\n"
else
    printf "\nError: Make failed, $FILE not found\n"
fi
