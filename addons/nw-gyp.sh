#!/bin/sh

nw-gyp clean

nw-gyp configure --target=0.13.0-beta2

nw-gyp build