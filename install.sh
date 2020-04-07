#!/bin/bash

rm ./install.log 2>/dev/null 1>&2

dpkg-query -s wiringpi >> install.log
dpkg-query -W --showformat='${Status}\n' wiringpi

echo "Building node-wiring-pi ... "
node-gyp clean 2>&1 | tee -a ./install.log
node-gyp configure build 2>&1 | tee -a ./install.log
