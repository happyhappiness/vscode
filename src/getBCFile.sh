#!/bin/sh

MYCODE_DIR="/usr/info/code/cpp/LogMonitor/LogMonitor"
REPOS="httpd"
# parameter
PARENT_DIR="${MYCODE_DIR}/second/download/${REPOS}/repos"
for SUB_DIR in `ls ${PARENT_DIR}`
do  
    CODE_DIR="${PARENT_DIR}/${SUB_DIR}"
    echo "now processing ${CODE_DIR}"
    cd ${CODE_DIR}
    `make clean`
    `./configure`
    `bear make`
    `${SMARTLOG_DIR}/script/extract_command_11.pl compile_commands.json`
    `./build_ir.sh`
done
