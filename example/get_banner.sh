#!/bin/bash
# This script outputs a C statement
BUILD_DATE=$(date)
echo "printf(\"This binary was built on: %s\\n\", \"$BUILD_DATE\");"