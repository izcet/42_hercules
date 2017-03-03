#!/bin/sh
SCRIPT="bomb.sh"
TIME=""
TEST="2:13 PM 3/3/2017"

apt-get install at -y

cat "$SCRIPT" | at $TIME
