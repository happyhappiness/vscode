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

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/bftpdutmp.c -o /data/download/bftpd/bftpdutmp.c.bc
check
echo "1 /data/download/bftpd/bftpdutmp.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/commands.c -o /data/download/bftpd/commands.c.bc
check
echo "2 /data/download/bftpd/commands.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/commands_admin.c -o /data/download/bftpd/commands_admin.c.bc
check
echo "3 /data/download/bftpd/commands_admin.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/cwd.c -o /data/download/bftpd/cwd.c.bc
check
echo "4 /data/download/bftpd/cwd.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/dirlist.c -o /data/download/bftpd/dirlist.c.bc
check
echo "5 /data/download/bftpd/dirlist.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/list.c -o /data/download/bftpd/list.c.bc
check
echo "6 /data/download/bftpd/list.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/login.c -o /data/download/bftpd/login.c.bc
check
echo "7 /data/download/bftpd/login.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/logging.c -o /data/download/bftpd/logging.c.bc
check
echo "8 /data/download/bftpd/logging.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/main.c -o /data/download/bftpd/main.c.bc
check
echo "9 /data/download/bftpd/main.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/mystring.c -o /data/download/bftpd/mystring.c.bc
check
echo "10 /data/download/bftpd/mystring.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/options.c -o /data/download/bftpd/options.c.bc
check
echo "11 /data/download/bftpd/options.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /data/download/bftpd/md5.c -o /data/download/bftpd/md5.c.bc
check
echo "12 /data/download/bftpd/md5.c to bc" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/bftpdutmp.c -o /data/download/bftpd/bftpdutmp.c.ll
echo "1 /data/download/bftpd/bftpdutmp.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/commands.c -o /data/download/bftpd/commands.c.ll
echo "2 /data/download/bftpd/commands.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/commands_admin.c -o /data/download/bftpd/commands_admin.c.ll
echo "3 /data/download/bftpd/commands_admin.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/cwd.c -o /data/download/bftpd/cwd.c.ll
echo "4 /data/download/bftpd/cwd.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/dirlist.c -o /data/download/bftpd/dirlist.c.ll
echo "5 /data/download/bftpd/dirlist.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/list.c -o /data/download/bftpd/list.c.ll
echo "6 /data/download/bftpd/list.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/login.c -o /data/download/bftpd/login.c.ll
echo "7 /data/download/bftpd/login.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/logging.c -o /data/download/bftpd/logging.c.ll
echo "8 /data/download/bftpd/logging.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/main.c -o /data/download/bftpd/main.c.ll
echo "9 /data/download/bftpd/main.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/mystring.c -o /data/download/bftpd/mystring.c.ll
echo "10 /data/download/bftpd/mystring.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/options.c -o /data/download/bftpd/options.c.ll
echo "11 /data/download/bftpd/options.c to ll" >&2

cd /data/download/bftpd
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /data/download/bftpd/md5.c -o /data/download/bftpd/md5.c.ll
echo "12 /data/download/bftpd/md5.c to ll" >&2
echo "Total ir $total" >&2
echo "Succ ir $succ" >&2
