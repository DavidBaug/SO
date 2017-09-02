#!/bin/bash

cp ~/Dropbox/UGR/2º\ Grado/1er\ Cuatrimestre/SSOO/2ANIO/Practicas/Fedora14-x86-root_fs /tmp

cp ~/Dropbox/UGR/2º\ Grado/1er\ Cuatrimestre/SSOO/2ANIO/Practicas/kernel32-3.0.4 /tmp

cd ~
cd /tmp

chmod +x /tmp/kernel32-3.0.4

./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m 

exit