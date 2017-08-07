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

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/bftpdutmp.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/bftpdutmp.c.bc
check
echo "1 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/bftpdutmp.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands.c.bc
check
echo "2 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands_admin.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands_admin.c.bc
check
echo "3 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands_admin.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/cwd.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/cwd.c.bc
check
echo "4 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/cwd.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/dirlist.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/dirlist.c.bc
check
echo "5 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/dirlist.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/list.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/list.c.bc
check
echo "6 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/list.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/login.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/login.c.bc
check
echo "7 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/login.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/logging.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/logging.c.bc
check
echo "8 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/logging.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/main.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/main.c.bc
check
echo "9 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/main.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/mystring.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/mystring.c.bc
check
echo "10 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/mystring.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/options.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/options.c.bc
check
echo "11 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/options.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/md5.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/md5.c.bc
check
echo "12 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/md5.c to bc" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/bftpdutmp.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/bftpdutmp.c.ll
echo "1 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/bftpdutmp.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands.c.ll
echo "2 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands_admin.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands_admin.c.ll
echo "3 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/commands_admin.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/cwd.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/cwd.c.ll
echo "4 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/cwd.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/dirlist.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/dirlist.c.ll
echo "5 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/dirlist.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/list.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/list.c.ll
echo "6 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/list.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/login.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/login.c.ll
echo "7 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/login.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/logging.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/logging.c.ll
echo "8 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/logging.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/main.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/main.c.ll
echo "9 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/main.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/mystring.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/mystring.c.ll
echo "10 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/mystring.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/options.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/options.c.ll
echo "11 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/options.c to ll" >&2

cd /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/md5.c -o /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/md5.c.ll
echo "12 /usr/info/code/cpp/LogMonitor/LogMonitor/second/download/bftpd/bftpd/md5.c to ll" >&2
echo "Total ir $total" >&2
echo "Succ ir $succ" >&2
