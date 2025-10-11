#!/bin/bash
# This script outputs a C statement
BUILD_DATE=$(date)
echo "printf(\"This binary was built $1 on: %s\\n\", \"$BUILD_DATE\");"