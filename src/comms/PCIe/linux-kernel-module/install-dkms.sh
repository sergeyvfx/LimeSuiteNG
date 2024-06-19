#!/bin/sh

# This script takes care of the full build and install pipeline of
# a specified module using DKMS.

set -e

MODULE_NAME=$1
MODULE_VERSION=$2
if [ -z "${MODULE_NAME}" ] || [ -z "${MODULE_VERSION}" ]; then
    echo "Error: Kernel module name or version is not specified"
    exit 1
fi

if [ `id -u` != 0 ] ; then
    echo "Error: Script must be run with root permissions"
    exit 1
fi

echo "Installing ${MODULE_NAME} version ${MODULE_VERSION}..."

BASEDIR=$(dirname "$0")

if [ ! -z "`dkms status ${MODULE_NAME}/${MODULE_VERSION}`" ]; then
    echo "Removing previously added DKMS module..."
    sudo dkms remove -m ${MODULE_NAME} -v ${MODULE_VERSION}
fi

echo "Adding module to the DKMS..."
sudo dkms add ${BASEDIR}

echo "Building the module..."
sudo dkms build -m ${MODULE_NAME} -v ${MODULE_VERSION}

echo "Installing the module..."
sudo dkms install -m ${MODULE_NAME} -v ${MODULE_VERSION}

exit 0
