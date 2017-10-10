#!/bin/bash



###This bash script is automatically produced by "extract_command.pl compile_commands.json", DO NOT CHANGE!###

total=0;
succ=0;
check(){
	if [ $? -eq 0 ]
	then
		succ=`expr $succ + 1`;
	fi
	total=`expr $total + 1`;
}

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I. -I.. -I../intl -DLOCALEDIR=\"/usr/local/share/locale\" -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/grep.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/grep.c.bc
check
echo "1 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/grep.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I. -I.. -I../intl -DLOCALEDIR=\"/usr/local/share/locale\" -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/dfa.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/dfa.c.bc
check
echo "2 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/dfa.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I. -I.. -I../intl -DLOCALEDIR=\"/usr/local/share/locale\" -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/kwset.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/kwset.c.bc
check
echo "3 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/kwset.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I. -I.. -I../intl -DLOCALEDIR=\"/usr/local/share/locale\" -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/obstack.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/obstack.c.bc
check
echo "4 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/obstack.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I. -I.. -I../intl -DLOCALEDIR=\"/usr/local/share/locale\" -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/getopt.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/getopt.c.bc
check
echo "5 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/getopt.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I. -I.. -I../intl -DLOCALEDIR=\"/usr/local/share/locale\" -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/getopt1.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/getopt1.c.bc
check
echo "6 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/getopt1.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I. -I.. -I../intl -DLOCALEDIR=\"/usr/local/share/locale\" -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/search.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/search.c.bc
check
echo "7 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/search.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I. -I.. -I../intl -DLOCALEDIR=\"/usr/local/share/locale\" -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/regex.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/regex.c.bc
check
echo "8 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-2.2/src/regex.c to bc" >&2
echo "Total ir $total" >&2
echo "Succ ir $succ" >&2
