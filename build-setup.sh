#!/bin/bash


basedir=$(dirname ${0})
package_type=$(${basedir}/HPCC-Platform/cmake_modules/distrocheck.sh)
version=$(${basedir}/HPCC-Platform/cmake_modules/getpackagerevisionarch.sh -n)

if [[ "${package_type}" == "DEB" ]]; then
    if [[ "${version}" == "xenial" || "${version}" == "zesty" ]]; then
        #Ubuntu 16.04 Xenial
        apt-get update
        apt-get install -y  libantlr3-runtime-java
        pushd /usr/share/java
        wget http://www.antlr.org/download/antlr-runtime-4.7.jar
        wget http://www.antlr.org/download/antlr-4.7-complete.jar
        popd
    else
        echo "Unsupported Debian version: ${version}"
    fi
elif [[ "${package_type}" == "RPM" ]]; then
    echo "haven't done this yet"
fi
