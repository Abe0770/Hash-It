#!/bin/bash
# HashIt Uninstaller v1.00

trap 'printf "\n"; exit' 2

printf "HashIt Ver 1.00 - Uninstall Script\n\n"

if [ "$EUID" -ne 0 ]; then
    echo "Permission denied! Please run this script as root."
    exit 1
fi

FILE=/usr/local/bin/getHash

if [ -f "$FILE" ]; then
    echo "Uninstalling HashIt..."
    rm "$FILE"
    echo "Removed successfully."
else
    echo "Error: HashIt is not installed or the binary was not found at $FILE"
fi
