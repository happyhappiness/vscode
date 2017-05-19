#!/bin/sh

# parameter
# CODE_DIR=${SQUID_DIR}
# CODE_DIR=${BFTPD_CODE}
# REPOS="BFTPD"
CODE_DIR=${GTK_CODE}
REPOS="GTK"

# code
echo "generating compiled_files.def:";
tmp=`${SMARTLOG_DIR}/script/extract_command.pl  ${CODE_DIR}/compile_commands.json`;
tmp=`mv ${MYCODE_DIR}/compiled_files.def ${CODE_DIR}/compiled_files.def`;

echo "generating logging_statement.out";
tmp=`cat ${CODE_DIR}/compiled_files.def | xargs clang-smartlog -find-logging-behavior > tmp.txt`;

echo "cp logging statement:";
tmp=`mv ${MYCODE_DIR}/logging_statement.out ${MYCODE_DIR}/data/fetch/${REPOS}_logging_statement.csv`;
# echo "run python file:";
# tmp=`python ${MYCODE_DIR}/src/cluster_context_with_function.py`;
# echo $tmp;