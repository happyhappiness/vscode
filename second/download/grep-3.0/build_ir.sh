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

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/argmatch.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/argmatch.c.bc
check
echo "1 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/argmatch.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/binary-io.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/binary-io.c.bc
check
echo "2 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/binary-io.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/bitrotate.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/bitrotate.c.bc
check
echo "3 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/bitrotate.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/c-ctype.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/c-ctype.c.bc
check
echo "4 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/c-ctype.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/c-strcasecmp.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/c-strcasecmp.c.bc
check
echo "5 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/c-strcasecmp.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/c-strncasecmp.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/c-strncasecmp.c.bc
check
echo "6 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/c-strncasecmp.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/cloexec.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/cloexec.c.bc
check
echo "7 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/cloexec.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/close-stream.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/close-stream.c.bc
check
echo "8 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/close-stream.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/closeout.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/closeout.c.bc
check
echo "9 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/closeout.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/cycle-check.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/cycle-check.c.bc
check
echo "10 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/cycle-check.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/dfa.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/dfa.c.bc
check
echo "11 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/dfa.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/localeinfo.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/localeinfo.c.bc
check
echo "12 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/localeinfo.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/opendir-safer.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/opendir-safer.c.bc
check
echo "13 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/opendir-safer.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/dirname-lgpl.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/dirname-lgpl.c.bc
check
echo "14 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/dirname-lgpl.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/basename-lgpl.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/basename-lgpl.c.bc
check
echo "15 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/basename-lgpl.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/stripslash.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/stripslash.c.bc
check
echo "16 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/stripslash.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/exclude.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/exclude.c.bc
check
echo "17 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/exclude.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/exitfail.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/exitfail.c.bc
check
echo "18 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/exitfail.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/creat-safer.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/creat-safer.c.bc
check
echo "19 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/creat-safer.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/open-safer.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/open-safer.c.bc
check
echo "20 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/open-safer.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fd-hook.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fd-hook.c.bc
check
echo "21 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fd-hook.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/filenamecat-lgpl.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/filenamecat-lgpl.c.bc
check
echo "22 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/filenamecat-lgpl.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/getprogname.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/getprogname.c.bc
check
echo "23 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/getprogname.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/hard-locale.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/hard-locale.c.bc
check
echo "24 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/hard-locale.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/hash.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/hash.c.bc
check
echo "25 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/hash.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/i-ring.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/i-ring.c.bc
check
echo "26 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/i-ring.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/localcharset.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/localcharset.c.bc
check
echo "27 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/localcharset.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/glthread/lock.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/glthread/lock.c.bc
check
echo "28 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/glthread/lock.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/malloca.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/malloca.c.bc
check
echo "29 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/malloca.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbchar.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbchar.c.bc
check
echo "30 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbchar.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbiter.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbiter.c.bc
check
echo "31 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbiter.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbscasecmp.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbscasecmp.c.bc
check
echo "32 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbscasecmp.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbslen.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbslen.c.bc
check
echo "33 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbslen.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbsstr.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbsstr.c.bc
check
echo "34 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbsstr.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbuiter.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbuiter.c.bc
check
echo "35 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbuiter.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/memchr2.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/memchr2.c.bc
check
echo "36 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/memchr2.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/openat-die.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/openat-die.c.bc
check
echo "37 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/openat-die.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/openat-safer.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/openat-safer.c.bc
check
echo "38 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/openat-safer.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/propername.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/propername.c.bc
check
echo "39 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/propername.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/quotearg.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/quotearg.c.bc
check
echo "40 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/quotearg.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/safe-read.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/safe-read.c.bc
check
echo "41 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/safe-read.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/save-cwd.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/save-cwd.c.bc
check
echo "42 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/save-cwd.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/striconv.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/striconv.c.bc
check
echo "43 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/striconv.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/strnlen1.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/strnlen1.c.bc
check
echo "44 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/strnlen1.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/glthread/threadlib.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/glthread/threadlib.c.bc
check
echo "45 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/glthread/threadlib.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/trim.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/trim.c.bc
check
echo "46 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/trim.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistd.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistd.c.bc
check
echo "47 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistd.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/dup-safer.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/dup-safer.c.bc
check
echo "48 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/dup-safer.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fd-safer.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fd-safer.c.bc
check
echo "49 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fd-safer.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/pipe-safer.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/pipe-safer.c.bc
check
echo "50 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/pipe-safer.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistr/u8-mbtoucr.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistr/u8-mbtoucr.c.bc
check
echo "51 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistr/u8-mbtoucr.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistr/u8-uctomb.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistr/u8-uctomb.c.bc
check
echo "52 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistr/u8-uctomb.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistr/u8-uctomb-aux.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistr/u8-uctomb-aux.c.bc
check
echo "53 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/unistr/u8-uctomb-aux.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/uniwidth/width.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/uniwidth/width.c.bc
check
echo "54 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/uniwidth/width.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/version-etc.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/version-etc.c.bc
check
echo "55 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/version-etc.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/version-etc-fsf.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/version-etc-fsf.c.bc
check
echo "56 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/version-etc-fsf.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/wctype-h.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/wctype-h.c.bc
check
echo "57 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/wctype-h.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xmalloc.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xmalloc.c.bc
check
echo "58 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xmalloc.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xalloc-die.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xalloc-die.c.bc
check
echo "59 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xalloc-die.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstriconv.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstriconv.c.bc
check
echo "60 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstriconv.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtoimax.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtoimax.c.bc
check
echo "61 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtoimax.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtol.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtol.c.bc
check
echo "62 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtol.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtoul.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtoul.c.bc
check
echo "63 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtoul.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtol-error.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtol-error.c.bc
check
echo "64 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/xstrtol-error.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/colorize.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/colorize.c.bc
check
echo "65 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/colorize.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/chdir-long.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/chdir-long.c.bc
check
echo "66 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/chdir-long.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fcntl.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fcntl.c.bc
check
echo "67 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fcntl.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fts.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fts.c.bc
check
echo "68 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/fts.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbrlen.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbrlen.c.bc
check
echo "69 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbrlen.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbrtowc.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbrtowc.c.bc
check
echo "70 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/mbrtowc.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/obstack.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/obstack.c.bc
check
echo "71 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/obstack.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/openat-proc.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/openat-proc.c.bc
check
echo "72 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/lib/openat-proc.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -I../lib -I../lib -I/usr/local/include -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/dfasearch.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/dfasearch.c.bc
check
echo "73 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/dfasearch.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -I../lib -I../lib -I/usr/local/include -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/grep.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/grep.c.bc
check
echo "74 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/grep.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -I../lib -I../lib -I/usr/local/include -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/kwsearch.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/kwsearch.c.bc
check
echo "75 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/kwsearch.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -I../lib -I../lib -I/usr/local/include -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/kwset.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/kwset.c.bc
check
echo "76 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/kwset.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -I../lib -I../lib -I/usr/local/include -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/pcresearch.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/pcresearch.c.bc
check
echo "77 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/pcresearch.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -I.. -I../lib -I../lib -I/usr/local/include -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/searchutils.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/searchutils.c.bc
check
echo "78 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/grep-3.0/src/searchutils.c to bc" >&2
echo "Total ir $total" >&2
echo "Succ ir $succ" >&2
