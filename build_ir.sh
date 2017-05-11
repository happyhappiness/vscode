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

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/assert.cc -o /data/download/squid/squid-3.5.25/compat/assert.cc.bc
check
echo "1 /data/download/squid/squid-3.5.25/compat/assert.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/compat.cc -o /data/download/squid/squid-3.5.25/compat/compat.cc.bc
check
echo "2 /data/download/squid/squid-3.5.25/compat/compat.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/debug.cc -o /data/download/squid/squid-3.5.25/compat/debug.cc.bc
check
echo "3 /data/download/squid/squid-3.5.25/compat/debug.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/eui64_aton.c -o /data/download/squid/squid-3.5.25/compat/eui64_aton.c.bc
check
echo "4 /data/download/squid/squid-3.5.25/compat/eui64_aton.c to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/getaddrinfo.cc -o /data/download/squid/squid-3.5.25/compat/getaddrinfo.cc.bc
check
echo "5 /data/download/squid/squid-3.5.25/compat/getaddrinfo.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/getnameinfo.cc -o /data/download/squid/squid-3.5.25/compat/getnameinfo.cc.bc
check
echo "6 /data/download/squid/squid-3.5.25/compat/getnameinfo.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/GnuRegex.c -o /data/download/squid/squid-3.5.25/compat/GnuRegex.c.bc
check
echo "7 /data/download/squid/squid-3.5.25/compat/GnuRegex.c to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/inet_ntop.cc -o /data/download/squid/squid-3.5.25/compat/inet_ntop.cc.bc
check
echo "8 /data/download/squid/squid-3.5.25/compat/inet_ntop.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/inet_pton.cc -o /data/download/squid/squid-3.5.25/compat/inet_pton.cc.bc
check
echo "9 /data/download/squid/squid-3.5.25/compat/inet_pton.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/memrchr.cc -o /data/download/squid/squid-3.5.25/compat/memrchr.cc.bc
check
echo "10 /data/download/squid/squid-3.5.25/compat/memrchr.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/shm.cc -o /data/download/squid/squid-3.5.25/compat/shm.cc.bc
check
echo "11 /data/download/squid/squid-3.5.25/compat/shm.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/statvfs.cc -o /data/download/squid/squid-3.5.25/compat/statvfs.cc.bc
check
echo "12 /data/download/squid/squid-3.5.25/compat/statvfs.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/strnstr.cc -o /data/download/squid/squid-3.5.25/compat/strnstr.cc.bc
check
echo "13 /data/download/squid/squid-3.5.25/compat/strnstr.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/strnrchr.c -o /data/download/squid/squid-3.5.25/compat/strnrchr.c.bc
check
echo "14 /data/download/squid/squid-3.5.25/compat/strnrchr.c to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/xalloc.cc -o /data/download/squid/squid-3.5.25/compat/xalloc.cc.bc
check
echo "15 /data/download/squid/squid-3.5.25/compat/xalloc.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/xstrerror.cc -o /data/download/squid/squid-3.5.25/compat/xstrerror.cc.bc
check
echo "16 /data/download/squid/squid-3.5.25/compat/xstrerror.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/xstring.cc -o /data/download/squid/squid-3.5.25/compat/xstring.cc.bc
check
echo "17 /data/download/squid/squid-3.5.25/compat/xstring.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/xstrto.cc -o /data/download/squid/squid-3.5.25/compat/xstrto.cc.bc
check
echo "18 /data/download/squid/squid-3.5.25/compat/xstrto.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/compat/mswindows.cc -o /data/download/squid/squid-3.5.25/compat/mswindows.cc.bc
check
echo "19 /data/download/squid/squid-3.5.25/compat/mswindows.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/asn1.c -o /data/download/squid/squid-3.5.25/lib/snmplib/asn1.c.bc
check
echo "20 /data/download/squid/squid-3.5.25/lib/snmplib/asn1.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/parse.c -o /data/download/squid/squid-3.5.25/lib/snmplib/parse.c.bc
check
echo "21 /data/download/squid/squid-3.5.25/lib/snmplib/parse.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/snmp_vars.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_vars.c.bc
check
echo "22 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_vars.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/coexistance.c -o /data/download/squid/squid-3.5.25/lib/snmplib/coexistance.c.bc
check
echo "23 /data/download/squid/squid-3.5.25/lib/snmplib/coexistance.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api.c.bc
check
echo "24 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/snmp_error.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_error.c.bc
check
echo "25 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_error.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/mib.c -o /data/download/squid/squid-3.5.25/lib/snmplib/mib.c.bc
check
echo "26 /data/download/squid/squid-3.5.25/lib/snmplib/mib.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api_error.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api_error.c.bc
check
echo "27 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api_error.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/snmp_msg.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_msg.c.bc
check
echo "28 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_msg.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/snmp_pdu.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_pdu.c.bc
check
echo "29 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_pdu.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/snmplib/snmplib_debug.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmplib_debug.c.bc
check
echo "30 /data/download/squid/squid-3.5.25/lib/snmplib/snmplib_debug.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/rfcnb
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-io.c -o /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-io.c.bc
check
echo "31 /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-io.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/rfcnb
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-util.c -o /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-util.c.bc
check
echo "32 /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-util.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/rfcnb
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/rfcnb/session.c -o /data/download/squid/squid-3.5.25/lib/rfcnb/session.c.bc
check
echo "33 /data/download/squid/squid-3.5.25/lib/rfcnb/session.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/smblib
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/smblib/md4.c -o /data/download/squid/squid-3.5.25/lib/smblib/md4.c.bc
check
echo "34 /data/download/squid/squid-3.5.25/lib/smblib/md4.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/smblib
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/smblib/smblib.c -o /data/download/squid/squid-3.5.25/lib/smblib/smblib.c.bc
check
echo "35 /data/download/squid/squid-3.5.25/lib/smblib/smblib.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/smblib
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/smblib/smblib-util.c -o /data/download/squid/squid-3.5.25/lib/smblib/smblib-util.c.bc
check
echo "36 /data/download/squid/squid-3.5.25/lib/smblib/smblib-util.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/smblib
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/smblib/smbencrypt.c -o /data/download/squid/squid-3.5.25/lib/smblib/smbencrypt.c.bc
check
echo "37 /data/download/squid/squid-3.5.25/lib/smblib/smbencrypt.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/smblib
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/smblib/smbdes.c -o /data/download/squid/squid-3.5.25/lib/smblib/smbdes.c.bc
check
echo "38 /data/download/squid/squid-3.5.25/lib/smblib/smbdes.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib/ntlmauth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/ntlmauth/ntlmauth.cc -o /data/download/squid/squid-3.5.25/lib/ntlmauth/ntlmauth.cc.bc
check
echo "39 /data/download/squid/squid-3.5.25/lib/ntlmauth/ntlmauth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/base64.c -o /data/download/squid/squid-3.5.25/lib/base64.c.bc
check
echo "40 /data/download/squid/squid-3.5.25/lib/base64.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/charset.c -o /data/download/squid/squid-3.5.25/lib/charset.c.bc
check
echo "41 /data/download/squid/squid-3.5.25/lib/charset.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/html_quote.c -o /data/download/squid/squid-3.5.25/lib/html_quote.c.bc
check
echo "42 /data/download/squid/squid-3.5.25/lib/html_quote.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/md5.c -o /data/download/squid/squid-3.5.25/lib/md5.c.bc
check
echo "43 /data/download/squid/squid-3.5.25/lib/md5.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/rfc1738.c -o /data/download/squid/squid-3.5.25/lib/rfc1738.c.bc
check
echo "44 /data/download/squid/squid-3.5.25/lib/rfc1738.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/rfc2617.c -o /data/download/squid/squid-3.5.25/lib/rfc2617.c.bc
check
echo "45 /data/download/squid/squid-3.5.25/lib/rfc2617.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/uudecode.c -o /data/download/squid/squid-3.5.25/lib/uudecode.c.bc
check
echo "46 /data/download/squid/squid-3.5.25/lib/uudecode.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/hash.cc -o /data/download/squid/squid-3.5.25/lib/hash.cc.bc
check
echo "47 /data/download/squid/squid-3.5.25/lib/hash.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/MemPool.cc -o /data/download/squid/squid-3.5.25/lib/MemPool.cc.bc
check
echo "48 /data/download/squid/squid-3.5.25/lib/MemPool.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/MemPoolChunked.cc -o /data/download/squid/squid-3.5.25/lib/MemPoolChunked.cc.bc
check
echo "49 /data/download/squid/squid-3.5.25/lib/MemPoolChunked.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/MemPoolMalloc.cc -o /data/download/squid/squid-3.5.25/lib/MemPoolMalloc.cc.bc
check
echo "50 /data/download/squid/squid-3.5.25/lib/MemPoolMalloc.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/getfullhostname.c -o /data/download/squid/squid-3.5.25/lib/getfullhostname.c.bc
check
echo "51 /data/download/squid/squid-3.5.25/lib/getfullhostname.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/heap.c -o /data/download/squid/squid-3.5.25/lib/heap.c.bc
check
echo "52 /data/download/squid/squid-3.5.25/lib/heap.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/iso3307.c -o /data/download/squid/squid-3.5.25/lib/iso3307.c.bc
check
echo "53 /data/download/squid/squid-3.5.25/lib/iso3307.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/radix.c -o /data/download/squid/squid-3.5.25/lib/radix.c.bc
check
echo "54 /data/download/squid/squid-3.5.25/lib/radix.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/rfc1035.c -o /data/download/squid/squid-3.5.25/lib/rfc1035.c.bc
check
echo "55 /data/download/squid/squid-3.5.25/lib/rfc1035.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/rfc1123.c -o /data/download/squid/squid-3.5.25/lib/rfc1123.c.bc
check
echo "56 /data/download/squid/squid-3.5.25/lib/rfc1123.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/rfc2671.c -o /data/download/squid/squid-3.5.25/lib/rfc2671.c.bc
check
echo "57 /data/download/squid/squid-3.5.25/lib/rfc2671.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/rfc3596.c -o /data/download/squid/squid-3.5.25/lib/rfc3596.c.bc
check
echo "58 /data/download/squid/squid-3.5.25/lib/rfc3596.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/Splay.cc -o /data/download/squid/squid-3.5.25/lib/Splay.cc.bc
check
echo "59 /data/download/squid/squid-3.5.25/lib/Splay.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/stub_memaccount.c -o /data/download/squid/squid-3.5.25/lib/stub_memaccount.c.bc
check
echo "60 /data/download/squid/squid-3.5.25/lib/stub_memaccount.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/util.c -o /data/download/squid/squid-3.5.25/lib/util.c.bc
check
echo "61 /data/download/squid/squid-3.5.25/lib/util.c to bc" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/lib/xusleep.c -o /data/download/squid/squid-3.5.25/lib/xusleep.c.bc
check
echo "62 /data/download/squid/squid-3.5.25/lib/xusleep.c to bc" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -c /data/download/squid/squid-3.5.25/libltdl/loaders/dlopen.c -o /data/download/squid/squid-3.5.25/libltdl/loaders/dlopen.c.bc
check
echo "63 /data/download/squid/squid-3.5.25/libltdl/loaders/dlopen.c to bc" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -c /data/download/squid/squid-3.5.25/libltdl/loaders/preopen.c -o /data/download/squid/squid-3.5.25/libltdl/loaders/preopen.c.bc
check
echo "64 /data/download/squid/squid-3.5.25/libltdl/loaders/preopen.c to bc" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -c /data/download/squid/squid-3.5.25/libltdl/lt__alloc.c -o /data/download/squid/squid-3.5.25/libltdl/lt__alloc.c.bc
check
echo "65 /data/download/squid/squid-3.5.25/libltdl/lt__alloc.c to bc" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -c /data/download/squid/squid-3.5.25/libltdl/lt_dlloader.c -o /data/download/squid/squid-3.5.25/libltdl/lt_dlloader.c.bc
check
echo "66 /data/download/squid/squid-3.5.25/libltdl/lt_dlloader.c to bc" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -c /data/download/squid/squid-3.5.25/libltdl/lt_error.c -o /data/download/squid/squid-3.5.25/libltdl/lt_error.c.bc
check
echo "67 /data/download/squid/squid-3.5.25/libltdl/lt_error.c to bc" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -c /data/download/squid/squid-3.5.25/libltdl/ltdl.c -o /data/download/squid/squid-3.5.25/libltdl/ltdl.c.bc
check
echo "68 /data/download/squid/squid-3.5.25/libltdl/ltdl.c to bc" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -c /data/download/squid/squid-3.5.25/libltdl/slist.c -o /data/download/squid/squid-3.5.25/libltdl/slist.c.bc
check
echo "69 /data/download/squid/squid-3.5.25/libltdl/slist.c to bc" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -c /data/download/squid/squid-3.5.25/libltdl/lt__strl.c -o /data/download/squid/squid-3.5.25/libltdl/lt__strl.c.bc
check
echo "70 /data/download/squid/squid-3.5.25/libltdl/lt__strl.c to bc" >&2

cd /data/download/squid/squid-3.5.25/libltdl/.libs
clang -g -emit-llvm -DPIC -c /data/download/squid/squid-3.5.25/libltdl/.libs/libltdlcS.c -o /data/download/squid/squid-3.5.25/libltdl/.libs/libltdlcS.c.bc
check
echo "71 /data/download/squid/squid-3.5.25/libltdl/.libs/libltdlcS.c to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/basic_ncsa_auth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/basic_ncsa_auth.cc.bc
check
echo "72 /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/basic_ncsa_auth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/crypt_md5.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/crypt_md5.cc.bc
check
echo "73 /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/crypt_md5.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/basic_nis_auth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/basic_nis_auth.cc.bc
check
echo "74 /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/basic_nis_auth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/nis_support.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/nis_support.cc.bc
check
echo "75 /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/nis_support.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/basic_radius_auth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/basic_radius_auth.cc.bc
check
echo "76 /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/basic_radius_auth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/radius-util.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/radius-util.cc.bc
check
echo "77 /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/radius-util.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -DHELPERSCRIPT=\"/usr/local/squid/libexec/basic_smb_auth.sh\" -c /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB/basic_smb_auth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB/basic_smb_auth.cc.bc
check
echo "78 /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB/basic_smb_auth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -I../../../lib -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/msntauth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/msntauth.cc.bc
check
echo "79 /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/msntauth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -I../../../lib -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/valid.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/valid.cc.bc
check
echo "80 /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/valid.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/fake
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/basic_auth/fake/fake.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/fake/fake.cc.bc
check
echo "81 /data/download/squid/squid-3.5.25/helpers/basic_auth/fake/fake.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/getpwnam
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/basic_auth/getpwnam/basic_getpwnam_auth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/getpwnam/basic_getpwnam_auth.cc.bc
check
echo "82 /data/download/squid/squid-3.5.25/helpers/basic_auth/getpwnam/basic_getpwnam_auth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/digest_auth/file
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/digest_auth/file/digest_file_auth.cc -o /data/download/squid/squid-3.5.25/helpers/digest_auth/file/digest_file_auth.cc.bc
check
echo "83 /data/download/squid/squid-3.5.25/helpers/digest_auth/file/digest_file_auth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/digest_auth/file
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/digest_auth/file/text_backend.cc -o /data/download/squid/squid-3.5.25/helpers/digest_auth/file/text_backend.cc.bc
check
echo "84 /data/download/squid/squid-3.5.25/helpers/digest_auth/file/text_backend.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/external_acl/file_userip
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/external_acl/file_userip/ext_file_userip_acl.cc -o /data/download/squid/squid-3.5.25/helpers/external_acl/file_userip/ext_file_userip_acl.cc.bc
check
echo "85 /data/download/squid/squid-3.5.25/helpers/external_acl/file_userip/ext_file_userip_acl.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/external_acl/unix_group
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/external_acl/unix_group/check_group.cc -o /data/download/squid/squid-3.5.25/helpers/external_acl/unix_group/check_group.cc.bc
check
echo "86 /data/download/squid/squid-3.5.25/helpers/external_acl/unix_group/check_group.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/log_daemon/file
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/log_daemon/file/log_file_daemon.cc -o /data/download/squid/squid-3.5.25/helpers/log_daemon/file/log_file_daemon.cc.bc
check
echo "87 /data/download/squid/squid-3.5.25/helpers/log_daemon/file/log_file_daemon.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/negotiate_auth/wrapper
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/negotiate_auth/wrapper/negotiate_wrapper.cc -o /data/download/squid/squid-3.5.25/helpers/negotiate_auth/wrapper/negotiate_wrapper.cc.bc
check
echo "88 /data/download/squid/squid-3.5.25/helpers/negotiate_auth/wrapper/negotiate_wrapper.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/url_rewrite/fake
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/url_rewrite/fake/fake.cc -o /data/download/squid/squid-3.5.25/helpers/url_rewrite/fake/fake.cc.bc
check
echo "89 /data/download/squid/squid-3.5.25/helpers/url_rewrite/fake/fake.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/ntlm_auth/fake
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I../../../lib -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/ntlm_auth/fake/ntlm_fake_auth.cc -o /data/download/squid/squid-3.5.25/helpers/ntlm_auth/fake/ntlm_fake_auth.cc.bc
check
echo "90 /data/download/squid/squid-3.5.25/helpers/ntlm_auth/fake/ntlm_fake_auth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/helpers/ntlm_auth/smb_lm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I../../../lib -D_REENTRANT -c /data/download/squid/squid-3.5.25/helpers/ntlm_auth/smb_lm/ntlm_smb_lm_auth.cc -o /data/download/squid/squid-3.5.25/helpers/ntlm_auth/smb_lm/ntlm_smb_lm_auth.cc.bc
check
echo "91 /data/download/squid/squid-3.5.25/helpers/ntlm_auth/smb_lm/ntlm_smb_lm_auth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -I. -I../include/ -I../src", -c /data/download/squid/squid-3.5.25/src/./cf_gen.cc -o /data/download/squid/squid-3.5.25/src/./cf_gen.cc.bc
check
echo "92 /data/download/squid/squid-3.5.25/src/./cf_gen.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/base/AsyncCall.cc -o /data/download/squid/squid-3.5.25/src/base/AsyncCall.cc.bc
check
echo "93 /data/download/squid/squid-3.5.25/src/base/AsyncCall.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/base/AsyncJob.cc -o /data/download/squid/squid-3.5.25/src/base/AsyncJob.cc.bc
check
echo "94 /data/download/squid/squid-3.5.25/src/base/AsyncJob.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/base/AsyncCallQueue.cc -o /data/download/squid/squid-3.5.25/src/base/AsyncCallQueue.cc.bc
check
echo "95 /data/download/squid/squid-3.5.25/src/base/AsyncCallQueue.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/base/CharacterSet.cc -o /data/download/squid/squid-3.5.25/src/base/CharacterSet.cc.bc
check
echo "96 /data/download/squid/squid-3.5.25/src/base/CharacterSet.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/base/RunnersRegistry.cc -o /data/download/squid/squid-3.5.25/src/base/RunnersRegistry.cc.bc
check
echo "97 /data/download/squid/squid-3.5.25/src/base/RunnersRegistry.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/base/TextException.cc -o /data/download/squid/squid-3.5.25/src/base/TextException.cc.bc
check
echo "98 /data/download/squid/squid-3.5.25/src/base/TextException.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/anyp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/anyp/PortCfg.cc -o /data/download/squid/squid-3.5.25/src/anyp/PortCfg.cc.bc
check
echo "99 /data/download/squid/squid-3.5.25/src/anyp/PortCfg.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/anyp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/anyp/ProtocolType.cc -o /data/download/squid/squid-3.5.25/src/anyp/ProtocolType.cc.bc
check
echo "100 /data/download/squid/squid-3.5.25/src/anyp/ProtocolType.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/anyp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/anyp/UriScheme.cc -o /data/download/squid/squid-3.5.25/src/anyp/UriScheme.cc.bc
check
echo "101 /data/download/squid/squid-3.5.25/src/anyp/UriScheme.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/helper
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/helper/ChildConfig.cc -o /data/download/squid/squid-3.5.25/src/helper/ChildConfig.cc.bc
check
echo "102 /data/download/squid/squid-3.5.25/src/helper/ChildConfig.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/helper
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/helper/Reply.cc -o /data/download/squid/squid-3.5.25/src/helper/Reply.cc.bc
check
echo "103 /data/download/squid/squid-3.5.25/src/helper/Reply.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ftp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ftp/Elements.cc -o /data/download/squid/squid-3.5.25/src/ftp/Elements.cc.bc
check
echo "104 /data/download/squid/squid-3.5.25/src/ftp/Elements.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ftp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ftp/Parsing.cc -o /data/download/squid/squid-3.5.25/src/ftp/Parsing.cc.bc
check
echo "105 /data/download/squid/squid-3.5.25/src/ftp/Parsing.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/parser
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/parser/Tokenizer.cc -o /data/download/squid/squid-3.5.25/src/parser/Tokenizer.cc.bc
check
echo "106 /data/download/squid/squid-3.5.25/src/parser/Tokenizer.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/AcceptLimiter.cc -o /data/download/squid/squid-3.5.25/src/comm/AcceptLimiter.cc.bc
check
echo "107 /data/download/squid/squid-3.5.25/src/comm/AcceptLimiter.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/ConnOpener.cc -o /data/download/squid/squid-3.5.25/src/comm/ConnOpener.cc.bc
check
echo "108 /data/download/squid/squid-3.5.25/src/comm/ConnOpener.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/Connection.cc -o /data/download/squid/squid-3.5.25/src/comm/Connection.cc.bc
check
echo "109 /data/download/squid/squid-3.5.25/src/comm/Connection.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/IoCallback.cc -o /data/download/squid/squid-3.5.25/src/comm/IoCallback.cc.bc
check
echo "110 /data/download/squid/squid-3.5.25/src/comm/IoCallback.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/ModDevPoll.cc -o /data/download/squid/squid-3.5.25/src/comm/ModDevPoll.cc.bc
check
echo "111 /data/download/squid/squid-3.5.25/src/comm/ModDevPoll.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/ModEpoll.cc -o /data/download/squid/squid-3.5.25/src/comm/ModEpoll.cc.bc
check
echo "112 /data/download/squid/squid-3.5.25/src/comm/ModEpoll.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/ModKqueue.cc -o /data/download/squid/squid-3.5.25/src/comm/ModKqueue.cc.bc
check
echo "113 /data/download/squid/squid-3.5.25/src/comm/ModKqueue.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/ModPoll.cc -o /data/download/squid/squid-3.5.25/src/comm/ModPoll.cc.bc
check
echo "114 /data/download/squid/squid-3.5.25/src/comm/ModPoll.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/ModSelect.cc -o /data/download/squid/squid-3.5.25/src/comm/ModSelect.cc.bc
check
echo "115 /data/download/squid/squid-3.5.25/src/comm/ModSelect.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/ModSelectWin32.cc -o /data/download/squid/squid-3.5.25/src/comm/ModSelectWin32.cc.bc
check
echo "116 /data/download/squid/squid-3.5.25/src/comm/ModSelectWin32.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/Read.cc -o /data/download/squid/squid-3.5.25/src/comm/Read.cc.bc
check
echo "117 /data/download/squid/squid-3.5.25/src/comm/Read.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/TcpAcceptor.cc -o /data/download/squid/squid-3.5.25/src/comm/TcpAcceptor.cc.bc
check
echo "118 /data/download/squid/squid-3.5.25/src/comm/TcpAcceptor.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm/Write.cc -o /data/download/squid/squid-3.5.25/src/comm/Write.cc.bc
check
echo "119 /data/download/squid/squid-3.5.25/src/comm/Write.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/eui
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/eui/Config.cc -o /data/download/squid/squid-3.5.25/src/eui/Config.cc.bc
check
echo "120 /data/download/squid/squid-3.5.25/src/eui/Config.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/eui
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/eui/Eui48.cc -o /data/download/squid/squid-3.5.25/src/eui/Eui48.cc.bc
check
echo "121 /data/download/squid/squid-3.5.25/src/eui/Eui48.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/eui
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/eui/Eui64.cc -o /data/download/squid/squid-3.5.25/src/eui/Eui64.cc.bc
check
echo "122 /data/download/squid/squid-3.5.25/src/eui/Eui64.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Acl.cc -o /data/download/squid/squid-3.5.25/src/acl/Acl.cc.bc
check
echo "123 /data/download/squid/squid-3.5.25/src/acl/Acl.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/BoolOps.cc -o /data/download/squid/squid-3.5.25/src/acl/BoolOps.cc.bc
check
echo "124 /data/download/squid/squid-3.5.25/src/acl/BoolOps.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Checklist.cc -o /data/download/squid/squid-3.5.25/src/acl/Checklist.cc.bc
check
echo "125 /data/download/squid/squid-3.5.25/src/acl/Checklist.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/InnerNode.cc -o /data/download/squid/squid-3.5.25/src/acl/InnerNode.cc.bc
check
echo "126 /data/download/squid/squid-3.5.25/src/acl/InnerNode.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Tree.cc -o /data/download/squid/squid-3.5.25/src/acl/Tree.cc.bc
check
echo "127 /data/download/squid/squid-3.5.25/src/acl/Tree.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Strategised.cc -o /data/download/squid/squid-3.5.25/src/acl/Strategised.cc.bc
check
echo "128 /data/download/squid/squid-3.5.25/src/acl/Strategised.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/FilledChecklist.cc -o /data/download/squid/squid-3.5.25/src/acl/FilledChecklist.cc.bc
check
echo "129 /data/download/squid/squid-3.5.25/src/acl/FilledChecklist.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/AclAddress.cc -o /data/download/squid/squid-3.5.25/src/acl/AclAddress.cc.bc
check
echo "130 /data/download/squid/squid-3.5.25/src/acl/AclAddress.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/IntRange.cc -o /data/download/squid/squid-3.5.25/src/acl/IntRange.cc.bc
check
echo "131 /data/download/squid/squid-3.5.25/src/acl/IntRange.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/RegexData.cc -o /data/download/squid/squid-3.5.25/src/acl/RegexData.cc.bc
check
echo "132 /data/download/squid/squid-3.5.25/src/acl/RegexData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/StringData.cc -o /data/download/squid/squid-3.5.25/src/acl/StringData.cc.bc
check
echo "133 /data/download/squid/squid-3.5.25/src/acl/StringData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Time.cc -o /data/download/squid/squid-3.5.25/src/acl/Time.cc.bc
check
echo "134 /data/download/squid/squid-3.5.25/src/acl/Time.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/TimeData.cc -o /data/download/squid/squid-3.5.25/src/acl/TimeData.cc.bc
check
echo "135 /data/download/squid/squid-3.5.25/src/acl/TimeData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/AllOf.cc -o /data/download/squid/squid-3.5.25/src/acl/AllOf.cc.bc
check
echo "136 /data/download/squid/squid-3.5.25/src/acl/AllOf.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/AnyOf.cc -o /data/download/squid/squid-3.5.25/src/acl/AnyOf.cc.bc
check
echo "137 /data/download/squid/squid-3.5.25/src/acl/AnyOf.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Asn.cc -o /data/download/squid/squid-3.5.25/src/acl/Asn.cc.bc
check
echo "138 /data/download/squid/squid-3.5.25/src/acl/Asn.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Browser.cc -o /data/download/squid/squid-3.5.25/src/acl/Browser.cc.bc
check
echo "139 /data/download/squid/squid-3.5.25/src/acl/Browser.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/DestinationDomain.cc -o /data/download/squid/squid-3.5.25/src/acl/DestinationDomain.cc.bc
check
echo "140 /data/download/squid/squid-3.5.25/src/acl/DestinationDomain.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/DestinationIp.cc -o /data/download/squid/squid-3.5.25/src/acl/DestinationIp.cc.bc
check
echo "141 /data/download/squid/squid-3.5.25/src/acl/DestinationIp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/DomainData.cc -o /data/download/squid/squid-3.5.25/src/acl/DomainData.cc.bc
check
echo "142 /data/download/squid/squid-3.5.25/src/acl/DomainData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/ExtUser.cc -o /data/download/squid/squid-3.5.25/src/acl/ExtUser.cc.bc
check
echo "143 /data/download/squid/squid-3.5.25/src/acl/ExtUser.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/HierCodeData.cc -o /data/download/squid/squid-3.5.25/src/acl/HierCodeData.cc.bc
check
echo "144 /data/download/squid/squid-3.5.25/src/acl/HierCodeData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/HierCode.cc -o /data/download/squid/squid-3.5.25/src/acl/HierCode.cc.bc
check
echo "145 /data/download/squid/squid-3.5.25/src/acl/HierCode.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/HttpHeaderData.cc -o /data/download/squid/squid-3.5.25/src/acl/HttpHeaderData.cc.bc
check
echo "146 /data/download/squid/squid-3.5.25/src/acl/HttpHeaderData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/HttpRepHeader.cc -o /data/download/squid/squid-3.5.25/src/acl/HttpRepHeader.cc.bc
check
echo "147 /data/download/squid/squid-3.5.25/src/acl/HttpRepHeader.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/HttpReqHeader.cc -o /data/download/squid/squid-3.5.25/src/acl/HttpReqHeader.cc.bc
check
echo "148 /data/download/squid/squid-3.5.25/src/acl/HttpReqHeader.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/HttpStatus.cc -o /data/download/squid/squid-3.5.25/src/acl/HttpStatus.cc.bc
check
echo "149 /data/download/squid/squid-3.5.25/src/acl/HttpStatus.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Ip.cc -o /data/download/squid/squid-3.5.25/src/acl/Ip.cc.bc
check
echo "150 /data/download/squid/squid-3.5.25/src/acl/Ip.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/LocalIp.cc -o /data/download/squid/squid-3.5.25/src/acl/LocalIp.cc.bc
check
echo "151 /data/download/squid/squid-3.5.25/src/acl/LocalIp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/LocalPort.cc -o /data/download/squid/squid-3.5.25/src/acl/LocalPort.cc.bc
check
echo "152 /data/download/squid/squid-3.5.25/src/acl/LocalPort.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/MaxConnection.cc -o /data/download/squid/squid-3.5.25/src/acl/MaxConnection.cc.bc
check
echo "153 /data/download/squid/squid-3.5.25/src/acl/MaxConnection.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Method.cc -o /data/download/squid/squid-3.5.25/src/acl/Method.cc.bc
check
echo "154 /data/download/squid/squid-3.5.25/src/acl/Method.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/MethodData.cc -o /data/download/squid/squid-3.5.25/src/acl/MethodData.cc.bc
check
echo "155 /data/download/squid/squid-3.5.25/src/acl/MethodData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/MyPortName.cc -o /data/download/squid/squid-3.5.25/src/acl/MyPortName.cc.bc
check
echo "156 /data/download/squid/squid-3.5.25/src/acl/MyPortName.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Note.cc -o /data/download/squid/squid-3.5.25/src/acl/Note.cc.bc
check
echo "157 /data/download/squid/squid-3.5.25/src/acl/Note.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/NoteData.cc -o /data/download/squid/squid-3.5.25/src/acl/NoteData.cc.bc
check
echo "158 /data/download/squid/squid-3.5.25/src/acl/NoteData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/PeerName.cc -o /data/download/squid/squid-3.5.25/src/acl/PeerName.cc.bc
check
echo "159 /data/download/squid/squid-3.5.25/src/acl/PeerName.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Protocol.cc -o /data/download/squid/squid-3.5.25/src/acl/Protocol.cc.bc
check
echo "160 /data/download/squid/squid-3.5.25/src/acl/Protocol.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/ProtocolData.cc -o /data/download/squid/squid-3.5.25/src/acl/ProtocolData.cc.bc
check
echo "161 /data/download/squid/squid-3.5.25/src/acl/ProtocolData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Random.cc -o /data/download/squid/squid-3.5.25/src/acl/Random.cc.bc
check
echo "162 /data/download/squid/squid-3.5.25/src/acl/Random.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Referer.cc -o /data/download/squid/squid-3.5.25/src/acl/Referer.cc.bc
check
echo "163 /data/download/squid/squid-3.5.25/src/acl/Referer.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/ReplyMimeType.cc -o /data/download/squid/squid-3.5.25/src/acl/ReplyMimeType.cc.bc
check
echo "164 /data/download/squid/squid-3.5.25/src/acl/ReplyMimeType.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/RequestMimeType.cc -o /data/download/squid/squid-3.5.25/src/acl/RequestMimeType.cc.bc
check
echo "165 /data/download/squid/squid-3.5.25/src/acl/RequestMimeType.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/SourceDomain.cc -o /data/download/squid/squid-3.5.25/src/acl/SourceDomain.cc.bc
check
echo "166 /data/download/squid/squid-3.5.25/src/acl/SourceDomain.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/SourceIp.cc -o /data/download/squid/squid-3.5.25/src/acl/SourceIp.cc.bc
check
echo "167 /data/download/squid/squid-3.5.25/src/acl/SourceIp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Tag.cc -o /data/download/squid/squid-3.5.25/src/acl/Tag.cc.bc
check
echo "168 /data/download/squid/squid-3.5.25/src/acl/Tag.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Url.cc -o /data/download/squid/squid-3.5.25/src/acl/Url.cc.bc
check
echo "169 /data/download/squid/squid-3.5.25/src/acl/Url.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/UrlLogin.cc -o /data/download/squid/squid-3.5.25/src/acl/UrlLogin.cc.bc
check
echo "170 /data/download/squid/squid-3.5.25/src/acl/UrlLogin.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/UrlPath.cc -o /data/download/squid/squid-3.5.25/src/acl/UrlPath.cc.bc
check
echo "171 /data/download/squid/squid-3.5.25/src/acl/UrlPath.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/UrlPort.cc -o /data/download/squid/squid-3.5.25/src/acl/UrlPort.cc.bc
check
echo "172 /data/download/squid/squid-3.5.25/src/acl/UrlPort.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/UserData.cc -o /data/download/squid/squid-3.5.25/src/acl/UserData.cc.bc
check
echo "173 /data/download/squid/squid-3.5.25/src/acl/UserData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Gadgets.cc -o /data/download/squid/squid-3.5.25/src/acl/Gadgets.cc.bc
check
echo "174 /data/download/squid/squid-3.5.25/src/acl/Gadgets.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/AdaptationService.cc -o /data/download/squid/squid-3.5.25/src/acl/AdaptationService.cc.bc
check
echo "175 /data/download/squid/squid-3.5.25/src/acl/AdaptationService.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/AdaptationServiceData.cc -o /data/download/squid/squid-3.5.25/src/acl/AdaptationServiceData.cc.bc
check
echo "176 /data/download/squid/squid-3.5.25/src/acl/AdaptationServiceData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Arp.cc -o /data/download/squid/squid-3.5.25/src/acl/Arp.cc.bc
check
echo "177 /data/download/squid/squid-3.5.25/src/acl/Arp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/acl/Eui64.cc -o /data/download/squid/squid-3.5.25/src/acl/Eui64.cc.bc
check
echo "178 /data/download/squid/squid-3.5.25/src/acl/Eui64.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/format
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/format/Config.cc -o /data/download/squid/squid-3.5.25/src/format/Config.cc.bc
check
echo "179 /data/download/squid/squid-3.5.25/src/format/Config.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/format
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/format/Format.cc -o /data/download/squid/squid-3.5.25/src/format/Format.cc.bc
check
echo "180 /data/download/squid/squid-3.5.25/src/format/Format.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/format
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/format/Quoting.cc -o /data/download/squid/squid-3.5.25/src/format/Quoting.cc.bc
check
echo "181 /data/download/squid/squid-3.5.25/src/format/Quoting.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/format
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/format/Token.cc -o /data/download/squid/squid-3.5.25/src/format/Token.cc.bc
check
echo "182 /data/download/squid/squid-3.5.25/src/format/Token.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/clients
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/clients/Client.cc -o /data/download/squid/squid-3.5.25/src/clients/Client.cc.bc
check
echo "183 /data/download/squid/squid-3.5.25/src/clients/Client.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/clients
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/clients/FtpClient.cc -o /data/download/squid/squid-3.5.25/src/clients/FtpClient.cc.bc
check
echo "184 /data/download/squid/squid-3.5.25/src/clients/FtpClient.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/clients
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/clients/FtpGateway.cc -o /data/download/squid/squid-3.5.25/src/clients/FtpGateway.cc.bc
check
echo "185 /data/download/squid/squid-3.5.25/src/clients/FtpGateway.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/clients
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/clients/FtpRelay.cc -o /data/download/squid/squid-3.5.25/src/clients/FtpRelay.cc.bc
check
echo "186 /data/download/squid/squid-3.5.25/src/clients/FtpRelay.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/servers
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/servers/FtpServer.cc -o /data/download/squid/squid-3.5.25/src/servers/FtpServer.cc.bc
check
echo "187 /data/download/squid/squid-3.5.25/src/servers/FtpServer.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/servers
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/servers/HttpServer.cc -o /data/download/squid/squid-3.5.25/src/servers/HttpServer.cc.bc
check
echo "188 /data/download/squid/squid-3.5.25/src/servers/HttpServer.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/aufs/StoreFSaufs.cc -o /data/download/squid/squid-3.5.25/src/fs/aufs/StoreFSaufs.cc.bc
check
echo "189 /data/download/squid/squid-3.5.25/src/fs/aufs/StoreFSaufs.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/diskd/StoreFSdiskd.cc -o /data/download/squid/squid-3.5.25/src/fs/diskd/StoreFSdiskd.cc.bc
check
echo "190 /data/download/squid/squid-3.5.25/src/fs/diskd/StoreFSdiskd.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/rock/RockDbCell.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockDbCell.cc.bc
check
echo "191 /data/download/squid/squid-3.5.25/src/fs/rock/RockDbCell.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/rock/RockIoState.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockIoState.cc.bc
check
echo "192 /data/download/squid/squid-3.5.25/src/fs/rock/RockIoState.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/rock/RockIoRequests.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockIoRequests.cc.bc
check
echo "193 /data/download/squid/squid-3.5.25/src/fs/rock/RockIoRequests.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/rock/RockRebuild.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockRebuild.cc.bc
check
echo "194 /data/download/squid/squid-3.5.25/src/fs/rock/RockRebuild.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/rock/RockStoreFileSystem.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockStoreFileSystem.cc.bc
check
echo "195 /data/download/squid/squid-3.5.25/src/fs/rock/RockStoreFileSystem.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/rock/RockSwapDir.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockSwapDir.cc.bc
check
echo "196 /data/download/squid/squid-3.5.25/src/fs/rock/RockSwapDir.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/ufs/StoreFSufs.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/StoreFSufs.cc.bc
check
echo "197 /data/download/squid/squid-3.5.25/src/fs/ufs/StoreFSufs.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStoreState.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStoreState.cc.bc
check
echo "198 /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStoreState.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapDir.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapDir.cc.bc
check
echo "199 /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapDir.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStrategy.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStrategy.cc.bc
check
echo "200 /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStrategy.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/ufs/StoreSearchUFS.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/StoreSearchUFS.cc.bc
check
echo "201 /data/download/squid/squid-3.5.25/src/fs/ufs/StoreSearchUFS.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapLogParser.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapLogParser.cc.bc
check
echo "202 /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapLogParser.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/ufs/RebuildState.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/RebuildState.cc.bc
check
echo "203 /data/download/squid/squid-3.5.25/src/fs/ufs/RebuildState.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/fs/Module.cc -o /data/download/squid/squid-3.5.25/src/fs/Module.cc.bc
check
echo "204 /data/download/squid/squid-3.5.25/src/fs/Module.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/repl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/repl/lru/store_repl_lru.cc -o /data/download/squid/squid-3.5.25/src/repl/lru/store_repl_lru.cc.bc
check
echo "205 /data/download/squid/squid-3.5.25/src/repl/lru/store_repl_lru.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/basic
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/basic/Config.cc -o /data/download/squid/squid-3.5.25/src/auth/basic/Config.cc.bc
check
echo "206 /data/download/squid/squid-3.5.25/src/auth/basic/Config.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/basic
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/basic/Scheme.cc -o /data/download/squid/squid-3.5.25/src/auth/basic/Scheme.cc.bc
check
echo "207 /data/download/squid/squid-3.5.25/src/auth/basic/Scheme.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/basic
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/basic/User.cc -o /data/download/squid/squid-3.5.25/src/auth/basic/User.cc.bc
check
echo "208 /data/download/squid/squid-3.5.25/src/auth/basic/User.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/basic
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/basic/UserRequest.cc -o /data/download/squid/squid-3.5.25/src/auth/basic/UserRequest.cc.bc
check
echo "209 /data/download/squid/squid-3.5.25/src/auth/basic/UserRequest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/digest
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/digest/Config.cc -o /data/download/squid/squid-3.5.25/src/auth/digest/Config.cc.bc
check
echo "210 /data/download/squid/squid-3.5.25/src/auth/digest/Config.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/digest
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/digest/Scheme.cc -o /data/download/squid/squid-3.5.25/src/auth/digest/Scheme.cc.bc
check
echo "211 /data/download/squid/squid-3.5.25/src/auth/digest/Scheme.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/digest
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/digest/User.cc -o /data/download/squid/squid-3.5.25/src/auth/digest/User.cc.bc
check
echo "212 /data/download/squid/squid-3.5.25/src/auth/digest/User.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/digest
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/digest/UserRequest.cc -o /data/download/squid/squid-3.5.25/src/auth/digest/UserRequest.cc.bc
check
echo "213 /data/download/squid/squid-3.5.25/src/auth/digest/UserRequest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/negotiate
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/negotiate/Scheme.cc -o /data/download/squid/squid-3.5.25/src/auth/negotiate/Scheme.cc.bc
check
echo "214 /data/download/squid/squid-3.5.25/src/auth/negotiate/Scheme.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/negotiate
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/negotiate/Config.cc -o /data/download/squid/squid-3.5.25/src/auth/negotiate/Config.cc.bc
check
echo "215 /data/download/squid/squid-3.5.25/src/auth/negotiate/Config.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/negotiate
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/negotiate/User.cc -o /data/download/squid/squid-3.5.25/src/auth/negotiate/User.cc.bc
check
echo "216 /data/download/squid/squid-3.5.25/src/auth/negotiate/User.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/negotiate
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/negotiate/UserRequest.cc -o /data/download/squid/squid-3.5.25/src/auth/negotiate/UserRequest.cc.bc
check
echo "217 /data/download/squid/squid-3.5.25/src/auth/negotiate/UserRequest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/ntlm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/ntlm/Config.cc -o /data/download/squid/squid-3.5.25/src/auth/ntlm/Config.cc.bc
check
echo "218 /data/download/squid/squid-3.5.25/src/auth/ntlm/Config.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/ntlm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/ntlm/Scheme.cc -o /data/download/squid/squid-3.5.25/src/auth/ntlm/Scheme.cc.bc
check
echo "219 /data/download/squid/squid-3.5.25/src/auth/ntlm/Scheme.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/ntlm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/ntlm/User.cc -o /data/download/squid/squid-3.5.25/src/auth/ntlm/User.cc.bc
check
echo "220 /data/download/squid/squid-3.5.25/src/auth/ntlm/User.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth/ntlm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/ntlm/UserRequest.cc -o /data/download/squid/squid-3.5.25/src/auth/ntlm/UserRequest.cc.bc
check
echo "221 /data/download/squid/squid-3.5.25/src/auth/ntlm/UserRequest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/Type.cc -o /data/download/squid/squid-3.5.25/src/auth/Type.cc.bc
check
echo "222 /data/download/squid/squid-3.5.25/src/auth/Type.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/Config.cc -o /data/download/squid/squid-3.5.25/src/auth/Config.cc.bc
check
echo "223 /data/download/squid/squid-3.5.25/src/auth/Config.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/CredentialState.cc -o /data/download/squid/squid-3.5.25/src/auth/CredentialState.cc.bc
check
echo "224 /data/download/squid/squid-3.5.25/src/auth/CredentialState.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/Gadgets.cc -o /data/download/squid/squid-3.5.25/src/auth/Gadgets.cc.bc
check
echo "225 /data/download/squid/squid-3.5.25/src/auth/Gadgets.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/Scheme.cc -o /data/download/squid/squid-3.5.25/src/auth/Scheme.cc.bc
check
echo "226 /data/download/squid/squid-3.5.25/src/auth/Scheme.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/State.cc -o /data/download/squid/squid-3.5.25/src/auth/State.cc.bc
check
echo "227 /data/download/squid/squid-3.5.25/src/auth/State.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/User.cc -o /data/download/squid/squid-3.5.25/src/auth/User.cc.bc
check
echo "228 /data/download/squid/squid-3.5.25/src/auth/User.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/UserRequest.cc -o /data/download/squid/squid-3.5.25/src/auth/UserRequest.cc.bc
check
echo "229 /data/download/squid/squid-3.5.25/src/auth/UserRequest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/Acl.cc -o /data/download/squid/squid-3.5.25/src/auth/Acl.cc.bc
check
echo "230 /data/download/squid/squid-3.5.25/src/auth/Acl.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/AclMaxUserIp.cc -o /data/download/squid/squid-3.5.25/src/auth/AclMaxUserIp.cc.bc
check
echo "231 /data/download/squid/squid-3.5.25/src/auth/AclMaxUserIp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/auth/AclProxyAuth.cc -o /data/download/squid/squid-3.5.25/src/auth/AclProxyAuth.cc.bc
check
echo "232 /data/download/squid/squid-3.5.25/src/auth/AclProxyAuth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/http
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/http/MethodType.cc -o /data/download/squid/squid-3.5.25/src/http/MethodType.cc.bc
check
echo "233 /data/download/squid/squid-3.5.25/src/http/MethodType.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/http
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/http/StatusCode.cc -o /data/download/squid/squid-3.5.25/src/http/StatusCode.cc.bc
check
echo "234 /data/download/squid/squid-3.5.25/src/http/StatusCode.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/http
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/http/StatusLine.cc -o /data/download/squid/squid-3.5.25/src/http/StatusLine.cc.bc
check
echo "235 /data/download/squid/squid-3.5.25/src/http/StatusLine.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ip
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ip/Address.cc -o /data/download/squid/squid-3.5.25/src/ip/Address.cc.bc
check
echo "236 /data/download/squid/squid-3.5.25/src/ip/Address.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ip
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ip/Intercept.cc -o /data/download/squid/squid-3.5.25/src/ip/Intercept.cc.bc
check
echo "237 /data/download/squid/squid-3.5.25/src/ip/Intercept.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ip
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ip/QosConfig.cc -o /data/download/squid/squid-3.5.25/src/ip/QosConfig.cc.bc
check
echo "238 /data/download/squid/squid-3.5.25/src/ip/QosConfig.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ip
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ip/tools.cc -o /data/download/squid/squid-3.5.25/src/ip/tools.cc.bc
check
echo "239 /data/download/squid/squid-3.5.25/src/ip/tools.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/icmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=NULL -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/icmp/Icmp.cc -o /data/download/squid/squid-3.5.25/src/icmp/Icmp.cc.bc
check
echo "240 /data/download/squid/squid-3.5.25/src/icmp/Icmp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/icmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=NULL -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/icmp/IcmpSquid.cc -o /data/download/squid/squid-3.5.25/src/icmp/IcmpSquid.cc.bc
check
echo "241 /data/download/squid/squid-3.5.25/src/icmp/IcmpSquid.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/icmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=NULL -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/icmp/net_db.cc -o /data/download/squid/squid-3.5.25/src/icmp/net_db.cc.bc
check
echo "242 /data/download/squid/squid-3.5.25/src/icmp/net_db.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ident
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ident/AclIdent.cc -o /data/download/squid/squid-3.5.25/src/ident/AclIdent.cc.bc
check
echo "243 /data/download/squid/squid-3.5.25/src/ident/AclIdent.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ident
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ident/Ident.cc -o /data/download/squid/squid-3.5.25/src/ident/Ident.cc.bc
check
echo "244 /data/download/squid/squid-3.5.25/src/ident/Ident.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/access_log.cc -o /data/download/squid/squid-3.5.25/src/log/access_log.cc.bc
check
echo "245 /data/download/squid/squid-3.5.25/src/log/access_log.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/Config.cc -o /data/download/squid/squid-3.5.25/src/log/Config.cc.bc
check
echo "246 /data/download/squid/squid-3.5.25/src/log/Config.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/File.cc -o /data/download/squid/squid-3.5.25/src/log/File.cc.bc
check
echo "247 /data/download/squid/squid-3.5.25/src/log/File.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/FormatHttpdCombined.cc -o /data/download/squid/squid-3.5.25/src/log/FormatHttpdCombined.cc.bc
check
echo "248 /data/download/squid/squid-3.5.25/src/log/FormatHttpdCombined.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/FormatHttpdCommon.cc -o /data/download/squid/squid-3.5.25/src/log/FormatHttpdCommon.cc.bc
check
echo "249 /data/download/squid/squid-3.5.25/src/log/FormatHttpdCommon.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/FormatSquidCustom.cc -o /data/download/squid/squid-3.5.25/src/log/FormatSquidCustom.cc.bc
check
echo "250 /data/download/squid/squid-3.5.25/src/log/FormatSquidCustom.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/FormatSquidIcap.cc -o /data/download/squid/squid-3.5.25/src/log/FormatSquidIcap.cc.bc
check
echo "251 /data/download/squid/squid-3.5.25/src/log/FormatSquidIcap.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/FormatSquidNative.cc -o /data/download/squid/squid-3.5.25/src/log/FormatSquidNative.cc.bc
check
echo "252 /data/download/squid/squid-3.5.25/src/log/FormatSquidNative.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/FormatSquidReferer.cc -o /data/download/squid/squid-3.5.25/src/log/FormatSquidReferer.cc.bc
check
echo "253 /data/download/squid/squid-3.5.25/src/log/FormatSquidReferer.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/FormatSquidUseragent.cc -o /data/download/squid/squid-3.5.25/src/log/FormatSquidUseragent.cc.bc
check
echo "254 /data/download/squid/squid-3.5.25/src/log/FormatSquidUseragent.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/ModDaemon.cc -o /data/download/squid/squid-3.5.25/src/log/ModDaemon.cc.bc
check
echo "255 /data/download/squid/squid-3.5.25/src/log/ModDaemon.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/ModStdio.cc -o /data/download/squid/squid-3.5.25/src/log/ModStdio.cc.bc
check
echo "256 /data/download/squid/squid-3.5.25/src/log/ModStdio.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/ModSyslog.cc -o /data/download/squid/squid-3.5.25/src/log/ModSyslog.cc.bc
check
echo "257 /data/download/squid/squid-3.5.25/src/log/ModSyslog.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/ModUdp.cc -o /data/download/squid/squid-3.5.25/src/log/ModUdp.cc.bc
check
echo "258 /data/download/squid/squid-3.5.25/src/log/ModUdp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/CustomLog.cc -o /data/download/squid/squid-3.5.25/src/log/CustomLog.cc.bc
check
echo "259 /data/download/squid/squid-3.5.25/src/log/CustomLog.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/log/TcpLogger.cc -o /data/download/squid/squid-3.5.25/src/log/TcpLogger.cc.bc
check
echo "260 /data/download/squid/squid-3.5.25/src/log/TcpLogger.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/AtomicWord.cc -o /data/download/squid/squid-3.5.25/src/ipc/AtomicWord.cc.bc
check
echo "261 /data/download/squid/squid-3.5.25/src/ipc/AtomicWord.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/FdNotes.cc -o /data/download/squid/squid-3.5.25/src/ipc/FdNotes.cc.bc
check
echo "262 /data/download/squid/squid-3.5.25/src/ipc/FdNotes.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/Kid.cc -o /data/download/squid/squid-3.5.25/src/ipc/Kid.cc.bc
check
echo "263 /data/download/squid/squid-3.5.25/src/ipc/Kid.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/Kids.cc -o /data/download/squid/squid-3.5.25/src/ipc/Kids.cc.bc
check
echo "264 /data/download/squid/squid-3.5.25/src/ipc/Kids.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/MemMap.cc -o /data/download/squid/squid-3.5.25/src/ipc/MemMap.cc.bc
check
echo "265 /data/download/squid/squid-3.5.25/src/ipc/MemMap.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/Queue.cc -o /data/download/squid/squid-3.5.25/src/ipc/Queue.cc.bc
check
echo "266 /data/download/squid/squid-3.5.25/src/ipc/Queue.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/ReadWriteLock.cc -o /data/download/squid/squid-3.5.25/src/ipc/ReadWriteLock.cc.bc
check
echo "267 /data/download/squid/squid-3.5.25/src/ipc/ReadWriteLock.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/StartListening.cc -o /data/download/squid/squid-3.5.25/src/ipc/StartListening.cc.bc
check
echo "268 /data/download/squid/squid-3.5.25/src/ipc/StartListening.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/StoreMap.cc -o /data/download/squid/squid-3.5.25/src/ipc/StoreMap.cc.bc
check
echo "269 /data/download/squid/squid-3.5.25/src/ipc/StoreMap.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/StrandCoord.cc -o /data/download/squid/squid-3.5.25/src/ipc/StrandCoord.cc.bc
check
echo "270 /data/download/squid/squid-3.5.25/src/ipc/StrandCoord.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/StrandSearch.cc -o /data/download/squid/squid-3.5.25/src/ipc/StrandSearch.cc.bc
check
echo "271 /data/download/squid/squid-3.5.25/src/ipc/StrandSearch.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/SharedListen.cc -o /data/download/squid/squid-3.5.25/src/ipc/SharedListen.cc.bc
check
echo "272 /data/download/squid/squid-3.5.25/src/ipc/SharedListen.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/TypedMsgHdr.cc -o /data/download/squid/squid-3.5.25/src/ipc/TypedMsgHdr.cc.bc
check
echo "273 /data/download/squid/squid-3.5.25/src/ipc/TypedMsgHdr.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/Coordinator.cc -o /data/download/squid/squid-3.5.25/src/ipc/Coordinator.cc.bc
check
echo "274 /data/download/squid/squid-3.5.25/src/ipc/Coordinator.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/UdsOp.cc -o /data/download/squid/squid-3.5.25/src/ipc/UdsOp.cc.bc
check
echo "275 /data/download/squid/squid-3.5.25/src/ipc/UdsOp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/Port.cc -o /data/download/squid/squid-3.5.25/src/ipc/Port.cc.bc
check
echo "276 /data/download/squid/squid-3.5.25/src/ipc/Port.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/Strand.cc -o /data/download/squid/squid-3.5.25/src/ipc/Strand.cc.bc
check
echo "277 /data/download/squid/squid-3.5.25/src/ipc/Strand.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/Forwarder.cc -o /data/download/squid/squid-3.5.25/src/ipc/Forwarder.cc.bc
check
echo "278 /data/download/squid/squid-3.5.25/src/ipc/Forwarder.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/Inquirer.cc -o /data/download/squid/squid-3.5.25/src/ipc/Inquirer.cc.bc
check
echo "279 /data/download/squid/squid-3.5.25/src/ipc/Inquirer.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/mem/Page.cc -o /data/download/squid/squid-3.5.25/src/ipc/mem/Page.cc.bc
check
echo "280 /data/download/squid/squid-3.5.25/src/ipc/mem/Page.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/mem/PagePool.cc -o /data/download/squid/squid-3.5.25/src/ipc/mem/PagePool.cc.bc
check
echo "281 /data/download/squid/squid-3.5.25/src/ipc/mem/PagePool.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/mem/Pages.cc -o /data/download/squid/squid-3.5.25/src/ipc/mem/Pages.cc.bc
check
echo "282 /data/download/squid/squid-3.5.25/src/ipc/mem/Pages.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/mem/PageStack.cc -o /data/download/squid/squid-3.5.25/src/ipc/mem/PageStack.cc.bc
check
echo "283 /data/download/squid/squid-3.5.25/src/ipc/mem/PageStack.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/ipc/mem/Segment.cc -o /data/download/squid/squid-3.5.25/src/ipc/mem/Segment.cc.bc
check
echo "284 /data/download/squid/squid-3.5.25/src/ipc/mem/Segment.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/Action.cc -o /data/download/squid/squid-3.5.25/src/mgr/Action.cc.bc
check
echo "285 /data/download/squid/squid-3.5.25/src/mgr/Action.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/ActionParams.cc -o /data/download/squid/squid-3.5.25/src/mgr/ActionParams.cc.bc
check
echo "286 /data/download/squid/squid-3.5.25/src/mgr/ActionParams.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/ActionPasswordList.cc -o /data/download/squid/squid-3.5.25/src/mgr/ActionPasswordList.cc.bc
check
echo "287 /data/download/squid/squid-3.5.25/src/mgr/ActionPasswordList.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/ActionWriter.cc -o /data/download/squid/squid-3.5.25/src/mgr/ActionWriter.cc.bc
check
echo "288 /data/download/squid/squid-3.5.25/src/mgr/ActionWriter.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/BasicActions.cc -o /data/download/squid/squid-3.5.25/src/mgr/BasicActions.cc.bc
check
echo "289 /data/download/squid/squid-3.5.25/src/mgr/BasicActions.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/Command.cc -o /data/download/squid/squid-3.5.25/src/mgr/Command.cc.bc
check
echo "290 /data/download/squid/squid-3.5.25/src/mgr/Command.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/CountersAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/CountersAction.cc.bc
check
echo "291 /data/download/squid/squid-3.5.25/src/mgr/CountersAction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/Filler.cc -o /data/download/squid/squid-3.5.25/src/mgr/Filler.cc.bc
check
echo "292 /data/download/squid/squid-3.5.25/src/mgr/Filler.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/Forwarder.cc -o /data/download/squid/squid-3.5.25/src/mgr/Forwarder.cc.bc
check
echo "293 /data/download/squid/squid-3.5.25/src/mgr/Forwarder.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/FunAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/FunAction.cc.bc
check
echo "294 /data/download/squid/squid-3.5.25/src/mgr/FunAction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/InfoAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/InfoAction.cc.bc
check
echo "295 /data/download/squid/squid-3.5.25/src/mgr/InfoAction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/Inquirer.cc -o /data/download/squid/squid-3.5.25/src/mgr/Inquirer.cc.bc
check
echo "296 /data/download/squid/squid-3.5.25/src/mgr/Inquirer.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/IntervalAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/IntervalAction.cc.bc
check
echo "297 /data/download/squid/squid-3.5.25/src/mgr/IntervalAction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/IoAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/IoAction.cc.bc
check
echo "298 /data/download/squid/squid-3.5.25/src/mgr/IoAction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/Registration.cc -o /data/download/squid/squid-3.5.25/src/mgr/Registration.cc.bc
check
echo "299 /data/download/squid/squid-3.5.25/src/mgr/Registration.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/Request.cc -o /data/download/squid/squid-3.5.25/src/mgr/Request.cc.bc
check
echo "300 /data/download/squid/squid-3.5.25/src/mgr/Request.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/Response.cc -o /data/download/squid/squid-3.5.25/src/mgr/Response.cc.bc
check
echo "301 /data/download/squid/squid-3.5.25/src/mgr/Response.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/ServiceTimesAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/ServiceTimesAction.cc.bc
check
echo "302 /data/download/squid/squid-3.5.25/src/mgr/ServiceTimesAction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/StoreIoAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/StoreIoAction.cc.bc
check
echo "303 /data/download/squid/squid-3.5.25/src/mgr/StoreIoAction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/StoreToCommWriter.cc -o /data/download/squid/squid-3.5.25/src/mgr/StoreToCommWriter.cc.bc
check
echo "304 /data/download/squid/squid-3.5.25/src/mgr/StoreToCommWriter.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/QueryParams.cc -o /data/download/squid/squid-3.5.25/src/mgr/QueryParams.cc.bc
check
echo "305 /data/download/squid/squid-3.5.25/src/mgr/QueryParams.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/IntParam.cc -o /data/download/squid/squid-3.5.25/src/mgr/IntParam.cc.bc
check
echo "306 /data/download/squid/squid-3.5.25/src/mgr/IntParam.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/mgr/StringParam.cc -o /data/download/squid/squid-3.5.25/src/mgr/StringParam.cc.bc
check
echo "307 /data/download/squid/squid-3.5.25/src/mgr/StringParam.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/snmp/Forwarder.cc -o /data/download/squid/squid-3.5.25/src/snmp/Forwarder.cc.bc
check
echo "308 /data/download/squid/squid-3.5.25/src/snmp/Forwarder.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/snmp/Inquirer.cc -o /data/download/squid/squid-3.5.25/src/snmp/Inquirer.cc.bc
check
echo "309 /data/download/squid/squid-3.5.25/src/snmp/Inquirer.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/snmp/Pdu.cc -o /data/download/squid/squid-3.5.25/src/snmp/Pdu.cc.bc
check
echo "310 /data/download/squid/squid-3.5.25/src/snmp/Pdu.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/snmp/Request.cc -o /data/download/squid/squid-3.5.25/src/snmp/Request.cc.bc
check
echo "311 /data/download/squid/squid-3.5.25/src/snmp/Request.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/snmp/Response.cc -o /data/download/squid/squid-3.5.25/src/snmp/Response.cc.bc
check
echo "312 /data/download/squid/squid-3.5.25/src/snmp/Response.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/snmp/Session.cc -o /data/download/squid/squid-3.5.25/src/snmp/Session.cc.bc
check
echo "313 /data/download/squid/squid-3.5.25/src/snmp/Session.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/snmp/Var.cc -o /data/download/squid/squid-3.5.25/src/snmp/Var.cc.bc
check
echo "314 /data/download/squid/squid-3.5.25/src/snmp/Var.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/Client.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Client.cc.bc
check
echo "315 /data/download/squid/squid-3.5.25/src/adaptation/icap/Client.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/Config.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Config.cc.bc
check
echo "316 /data/download/squid/squid-3.5.25/src/adaptation/icap/Config.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/Elements.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Elements.cc.bc
check
echo "317 /data/download/squid/squid-3.5.25/src/adaptation/icap/Elements.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/Options.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Options.cc.bc
check
echo "318 /data/download/squid/squid-3.5.25/src/adaptation/icap/Options.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/ServiceRep.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/ServiceRep.cc.bc
check
echo "319 /data/download/squid/squid-3.5.25/src/adaptation/icap/ServiceRep.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/Launcher.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Launcher.cc.bc
check
echo "320 /data/download/squid/squid-3.5.25/src/adaptation/icap/Launcher.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/OptXact.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/OptXact.cc.bc
check
echo "321 /data/download/squid/squid-3.5.25/src/adaptation/icap/OptXact.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/Xaction.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Xaction.cc.bc
check
echo "322 /data/download/squid/squid-3.5.25/src/adaptation/icap/Xaction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/ModXact.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/ModXact.cc.bc
check
echo "323 /data/download/squid/squid-3.5.25/src/adaptation/icap/ModXact.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/icap_log.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/icap_log.cc.bc
check
echo "324 /data/download/squid/squid-3.5.25/src/adaptation/icap/icap_log.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/icap/History.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/History.cc.bc
check
echo "325 /data/download/squid/squid-3.5.25/src/adaptation/icap/History.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/AccessCheck.cc -o /data/download/squid/squid-3.5.25/src/adaptation/AccessCheck.cc.bc
check
echo "326 /data/download/squid/squid-3.5.25/src/adaptation/AccessCheck.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/AccessRule.cc -o /data/download/squid/squid-3.5.25/src/adaptation/AccessRule.cc.bc
check
echo "327 /data/download/squid/squid-3.5.25/src/adaptation/AccessRule.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/Answer.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Answer.cc.bc
check
echo "328 /data/download/squid/squid-3.5.25/src/adaptation/Answer.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/Config.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Config.cc.bc
check
echo "329 /data/download/squid/squid-3.5.25/src/adaptation/Config.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/DynamicGroupCfg.cc -o /data/download/squid/squid-3.5.25/src/adaptation/DynamicGroupCfg.cc.bc
check
echo "330 /data/download/squid/squid-3.5.25/src/adaptation/DynamicGroupCfg.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/Elements.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Elements.cc.bc
check
echo "331 /data/download/squid/squid-3.5.25/src/adaptation/Elements.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/Initiate.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Initiate.cc.bc
check
echo "332 /data/download/squid/squid-3.5.25/src/adaptation/Initiate.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/Initiator.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Initiator.cc.bc
check
echo "333 /data/download/squid/squid-3.5.25/src/adaptation/Initiator.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/Iterator.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Iterator.cc.bc
check
echo "334 /data/download/squid/squid-3.5.25/src/adaptation/Iterator.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/Message.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Message.cc.bc
check
echo "335 /data/download/squid/squid-3.5.25/src/adaptation/Message.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/Service.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Service.cc.bc
check
echo "336 /data/download/squid/squid-3.5.25/src/adaptation/Service.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/ServiceConfig.cc -o /data/download/squid/squid-3.5.25/src/adaptation/ServiceConfig.cc.bc
check
echo "337 /data/download/squid/squid-3.5.25/src/adaptation/ServiceConfig.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/ServiceGroups.cc -o /data/download/squid/squid-3.5.25/src/adaptation/ServiceGroups.cc.bc
check
echo "338 /data/download/squid/squid-3.5.25/src/adaptation/ServiceGroups.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/ServiceFilter.cc -o /data/download/squid/squid-3.5.25/src/adaptation/ServiceFilter.cc.bc
check
echo "339 /data/download/squid/squid-3.5.25/src/adaptation/ServiceFilter.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/adaptation/History.cc -o /data/download/squid/squid-3.5.25/src/adaptation/History.cc.bc
check
echo "340 /data/download/squid/squid-3.5.25/src/adaptation/History.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskFile.cc.bc
check
echo "341 /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskFile.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOStrategy.cc.bc
check
echo "342 /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOStrategy.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOModule.cc.bc
check
echo "343 /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOModule.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingFile.cc.bc
check
echo "344 /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingFile.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingIOStrategy.cc.bc
check
echo "345 /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingIOStrategy.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingDiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingDiskIOModule.cc.bc
check
echo "346 /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingDiskIOModule.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdFile.cc.bc
check
echo "347 /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdFile.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdIOStrategy.cc.bc
check
echo "348 /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdIOStrategy.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskDaemonDiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskDaemonDiskIOModule.cc.bc
check
echo "349 /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskDaemonDiskIOModule.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdAction.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdAction.cc.bc
check
echo "350 /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdAction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/aiops.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/aiops.cc.bc
check
echo "351 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/aiops.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/CommIO.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/CommIO.cc.bc
check
echo "352 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/CommIO.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/async_io.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/async_io.cc.bc
check
echo "353 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/async_io.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskFile.cc.bc
check
echo "354 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskFile.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskIOModule.cc.bc
check
echo "355 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskIOModule.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsIOStrategy.cc.bc
check
echo "356 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsIOStrategy.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoFile.cc.bc
check
echo "357 /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoFile.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoIOStrategy.cc.bc
check
echo "358 /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoIOStrategy.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoDiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoDiskIOModule.cc.bc
check
echo "359 /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoDiskIOModule.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedFile.cc.bc
check
echo "360 /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedFile.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedIOStrategy.cc.bc
check
echo "361 /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedIOStrategy.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedDiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedDiskIOModule.cc.bc
check
echo "362 /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedDiskIOModule.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/comm.cc -o /data/download/squid/squid-3.5.25/src/comm.cc.bc
check
echo "363 /data/download/squid/squid-3.5.25/src/comm.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/CommCalls.cc -o /data/download/squid/squid-3.5.25/src/CommCalls.cc.bc
check
echo "364 /data/download/squid/squid-3.5.25/src/CommCalls.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/DescriptorSet.cc -o /data/download/squid/squid-3.5.25/src/DescriptorSet.cc.bc
check
echo "365 /data/download/squid/squid-3.5.25/src/DescriptorSet.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -DPIC -c /data/download/squid/squid-3.5.25/src/SquidConfig.cc -o /data/download/squid/squid-3.5.25/src/SquidConfig.cc.bc
check
echo "366 /data/download/squid/squid-3.5.25/src/SquidConfig.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/diskd.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/diskd.cc.bc
check
echo "367 /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/diskd.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/time.cc -o /data/download/squid/squid-3.5.25/src/time.cc.bc
check
echo "368 /data/download/squid/squid-3.5.25/src/time.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/unlinkd_daemon.cc -o /data/download/squid/squid-3.5.25/src/unlinkd_daemon.cc.bc
check
echo "369 /data/download/squid/squid-3.5.25/src/unlinkd_daemon.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/AclRegs.cc -o /data/download/squid/squid-3.5.25/src/AclRegs.cc.bc
check
echo "370 /data/download/squid/squid-3.5.25/src/AclRegs.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/AuthReg.cc -o /data/download/squid/squid-3.5.25/src/AuthReg.cc.bc
check
echo "371 /data/download/squid/squid-3.5.25/src/AuthReg.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/AccessLogEntry.cc -o /data/download/squid/squid-3.5.25/src/AccessLogEntry.cc.bc
check
echo "372 /data/download/squid/squid-3.5.25/src/AccessLogEntry.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/AsyncEngine.cc -o /data/download/squid/squid-3.5.25/src/AsyncEngine.cc.bc
check
echo "373 /data/download/squid/squid-3.5.25/src/AsyncEngine.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/YesNoNone.cc -o /data/download/squid/squid-3.5.25/src/YesNoNone.cc.bc
check
echo "374 /data/download/squid/squid-3.5.25/src/YesNoNone.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/cache_cf.cc -o /data/download/squid/squid-3.5.25/src/cache_cf.cc.bc
check
echo "375 /data/download/squid/squid-3.5.25/src/cache_cf.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/CacheDigest.cc -o /data/download/squid/squid-3.5.25/src/CacheDigest.cc.bc
check
echo "376 /data/download/squid/squid-3.5.25/src/CacheDigest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/cache_manager.cc -o /data/download/squid/squid-3.5.25/src/cache_manager.cc.bc
check
echo "377 /data/download/squid/squid-3.5.25/src/cache_manager.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/carp.cc -o /data/download/squid/squid-3.5.25/src/carp.cc.bc
check
echo "378 /data/download/squid/squid-3.5.25/src/carp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/cbdata.cc -o /data/download/squid/squid-3.5.25/src/cbdata.cc.bc
check
echo "379 /data/download/squid/squid-3.5.25/src/cbdata.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/ChunkedCodingParser.cc -o /data/download/squid/squid-3.5.25/src/ChunkedCodingParser.cc.bc
check
echo "380 /data/download/squid/squid-3.5.25/src/ChunkedCodingParser.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/client_db.cc -o /data/download/squid/squid-3.5.25/src/client_db.cc.bc
check
echo "381 /data/download/squid/squid-3.5.25/src/client_db.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/client_side.cc -o /data/download/squid/squid-3.5.25/src/client_side.cc.bc
check
echo "382 /data/download/squid/squid-3.5.25/src/client_side.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/client_side_reply.cc -o /data/download/squid/squid-3.5.25/src/client_side_reply.cc.bc
check
echo "383 /data/download/squid/squid-3.5.25/src/client_side_reply.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/client_side_request.cc -o /data/download/squid/squid-3.5.25/src/client_side_request.cc.bc
check
echo "384 /data/download/squid/squid-3.5.25/src/client_side_request.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/BodyPipe.cc -o /data/download/squid/squid-3.5.25/src/BodyPipe.cc.bc
check
echo "385 /data/download/squid/squid-3.5.25/src/BodyPipe.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/clientStream.cc -o /data/download/squid/squid-3.5.25/src/clientStream.cc.bc
check
echo "386 /data/download/squid/squid-3.5.25/src/clientStream.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/CollapsedForwarding.cc -o /data/download/squid/squid-3.5.25/src/CollapsedForwarding.cc.bc
check
echo "387 /data/download/squid/squid-3.5.25/src/CollapsedForwarding.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/CompletionDispatcher.cc -o /data/download/squid/squid-3.5.25/src/CompletionDispatcher.cc.bc
check
echo "388 /data/download/squid/squid-3.5.25/src/CompletionDispatcher.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/ConfigOption.cc -o /data/download/squid/squid-3.5.25/src/ConfigOption.cc.bc
check
echo "389 /data/download/squid/squid-3.5.25/src/ConfigOption.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/ConfigParser.cc -o /data/download/squid/squid-3.5.25/src/ConfigParser.cc.bc
check
echo "390 /data/download/squid/squid-3.5.25/src/ConfigParser.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/CpuAffinity.cc -o /data/download/squid/squid-3.5.25/src/CpuAffinity.cc.bc
check
echo "391 /data/download/squid/squid-3.5.25/src/CpuAffinity.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/CpuAffinityMap.cc -o /data/download/squid/squid-3.5.25/src/CpuAffinityMap.cc.bc
check
echo "392 /data/download/squid/squid-3.5.25/src/CpuAffinityMap.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/CpuAffinitySet.cc -o /data/download/squid/squid-3.5.25/src/CpuAffinitySet.cc.bc
check
echo "393 /data/download/squid/squid-3.5.25/src/CpuAffinitySet.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/debug.cc -o /data/download/squid/squid-3.5.25/src/debug.cc.bc
check
echo "394 /data/download/squid/squid-3.5.25/src/debug.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/disk.cc -o /data/download/squid/squid-3.5.25/src/disk.cc.bc
check
echo "395 /data/download/squid/squid-3.5.25/src/disk.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModule.cc.bc
check
echo "396 /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModule.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/ReadRequest.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/ReadRequest.cc.bc
check
echo "397 /data/download/squid/squid-3.5.25/src/DiskIO/ReadRequest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/WriteRequest.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/WriteRequest.cc.bc
check
echo "398 /data/download/squid/squid-3.5.25/src/DiskIO/WriteRequest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/dlink.cc -o /data/download/squid/squid-3.5.25/src/dlink.cc.bc
check
echo "399 /data/download/squid/squid-3.5.25/src/dlink.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/dns_internal.cc -o /data/download/squid/squid-3.5.25/src/dns_internal.cc.bc
check
echo "400 /data/download/squid/squid-3.5.25/src/dns_internal.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DnsLookupDetails.cc -o /data/download/squid/squid-3.5.25/src/DnsLookupDetails.cc.bc
check
echo "401 /data/download/squid/squid-3.5.25/src/DnsLookupDetails.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/errorpage.cc -o /data/download/squid/squid-3.5.25/src/errorpage.cc.bc
check
echo "402 /data/download/squid/squid-3.5.25/src/errorpage.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/ETag.cc -o /data/download/squid/squid-3.5.25/src/ETag.cc.bc
check
echo "403 /data/download/squid/squid-3.5.25/src/ETag.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/event.cc -o /data/download/squid/squid-3.5.25/src/event.cc.bc
check
echo "404 /data/download/squid/squid-3.5.25/src/event.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/EventLoop.cc -o /data/download/squid/squid-3.5.25/src/EventLoop.cc.bc
check
echo "405 /data/download/squid/squid-3.5.25/src/EventLoop.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/external_acl.cc -o /data/download/squid/squid-3.5.25/src/external_acl.cc.bc
check
echo "406 /data/download/squid/squid-3.5.25/src/external_acl.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/ExternalACLEntry.cc -o /data/download/squid/squid-3.5.25/src/ExternalACLEntry.cc.bc
check
echo "407 /data/download/squid/squid-3.5.25/src/ExternalACLEntry.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/FadingCounter.cc -o /data/download/squid/squid-3.5.25/src/FadingCounter.cc.bc
check
echo "408 /data/download/squid/squid-3.5.25/src/FadingCounter.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/fatal.cc -o /data/download/squid/squid-3.5.25/src/fatal.cc.bc
check
echo "409 /data/download/squid/squid-3.5.25/src/fatal.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/fd.cc -o /data/download/squid/squid-3.5.25/src/fd.cc.bc
check
echo "410 /data/download/squid/squid-3.5.25/src/fd.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/fde.cc -o /data/download/squid/squid-3.5.25/src/fde.cc.bc
check
echo "411 /data/download/squid/squid-3.5.25/src/fde.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/filemap.cc -o /data/download/squid/squid-3.5.25/src/filemap.cc.bc
check
echo "412 /data/download/squid/squid-3.5.25/src/filemap.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/fqdncache.cc -o /data/download/squid/squid-3.5.25/src/fqdncache.cc.bc
check
echo "413 /data/download/squid/squid-3.5.25/src/fqdncache.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/FwdState.cc -o /data/download/squid/squid-3.5.25/src/FwdState.cc.bc
check
echo "414 /data/download/squid/squid-3.5.25/src/FwdState.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/gopher.cc -o /data/download/squid/squid-3.5.25/src/gopher.cc.bc
check
echo "415 /data/download/squid/squid-3.5.25/src/gopher.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/helper.cc -o /data/download/squid/squid-3.5.25/src/helper.cc.bc
check
echo "416 /data/download/squid/squid-3.5.25/src/helper.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/htcp.cc -o /data/download/squid/squid-3.5.25/src/htcp.cc.bc
check
echo "417 /data/download/squid/squid-3.5.25/src/htcp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/http.cc -o /data/download/squid/squid-3.5.25/src/http.cc.bc
check
echo "418 /data/download/squid/squid-3.5.25/src/http.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpHdrCc.cc -o /data/download/squid/squid-3.5.25/src/HttpHdrCc.cc.bc
check
echo "419 /data/download/squid/squid-3.5.25/src/HttpHdrCc.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpHdrRange.cc -o /data/download/squid/squid-3.5.25/src/HttpHdrRange.cc.bc
check
echo "420 /data/download/squid/squid-3.5.25/src/HttpHdrRange.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpHdrSc.cc -o /data/download/squid/squid-3.5.25/src/HttpHdrSc.cc.bc
check
echo "421 /data/download/squid/squid-3.5.25/src/HttpHdrSc.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpHdrScTarget.cc -o /data/download/squid/squid-3.5.25/src/HttpHdrScTarget.cc.bc
check
echo "422 /data/download/squid/squid-3.5.25/src/HttpHdrScTarget.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpHdrContRange.cc -o /data/download/squid/squid-3.5.25/src/HttpHdrContRange.cc.bc
check
echo "423 /data/download/squid/squid-3.5.25/src/HttpHdrContRange.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpHeader.cc -o /data/download/squid/squid-3.5.25/src/HttpHeader.cc.bc
check
echo "424 /data/download/squid/squid-3.5.25/src/HttpHeader.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpHeaderTools.cc -o /data/download/squid/squid-3.5.25/src/HttpHeaderTools.cc.bc
check
echo "425 /data/download/squid/squid-3.5.25/src/HttpHeaderTools.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpBody.cc -o /data/download/squid/squid-3.5.25/src/HttpBody.cc.bc
check
echo "426 /data/download/squid/squid-3.5.25/src/HttpBody.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpMsg.cc -o /data/download/squid/squid-3.5.25/src/HttpMsg.cc.bc
check
echo "427 /data/download/squid/squid-3.5.25/src/HttpMsg.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpParser.cc -o /data/download/squid/squid-3.5.25/src/HttpParser.cc.bc
check
echo "428 /data/download/squid/squid-3.5.25/src/HttpParser.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpReply.cc -o /data/download/squid/squid-3.5.25/src/HttpReply.cc.bc
check
echo "429 /data/download/squid/squid-3.5.25/src/HttpReply.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/RequestFlags.cc -o /data/download/squid/squid-3.5.25/src/RequestFlags.cc.bc
check
echo "430 /data/download/squid/squid-3.5.25/src/RequestFlags.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpRequest.cc -o /data/download/squid/squid-3.5.25/src/HttpRequest.cc.bc
check
echo "431 /data/download/squid/squid-3.5.25/src/HttpRequest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/HttpRequestMethod.cc -o /data/download/squid/squid-3.5.25/src/HttpRequestMethod.cc.bc
check
echo "432 /data/download/squid/squid-3.5.25/src/HttpRequestMethod.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/icp_v2.cc -o /data/download/squid/squid-3.5.25/src/icp_v2.cc.bc
check
echo "433 /data/download/squid/squid-3.5.25/src/icp_v2.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/icp_v3.cc -o /data/download/squid/squid-3.5.25/src/icp_v3.cc.bc
check
echo "434 /data/download/squid/squid-3.5.25/src/icp_v3.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/int.cc -o /data/download/squid/squid-3.5.25/src/int.cc.bc
check
echo "435 /data/download/squid/squid-3.5.25/src/int.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/internal.cc -o /data/download/squid/squid-3.5.25/src/internal.cc.bc
check
echo "436 /data/download/squid/squid-3.5.25/src/internal.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/ipc.cc -o /data/download/squid/squid-3.5.25/src/ipc.cc.bc
check
echo "437 /data/download/squid/squid-3.5.25/src/ipc.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/ipcache.cc -o /data/download/squid/squid-3.5.25/src/ipcache.cc.bc
check
echo "438 /data/download/squid/squid-3.5.25/src/ipcache.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/SquidList.cc -o /data/download/squid/squid-3.5.25/src/SquidList.cc.bc
check
echo "439 /data/download/squid/squid-3.5.25/src/SquidList.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/main.cc -o /data/download/squid/squid-3.5.25/src/main.cc.bc
check
echo "440 /data/download/squid/squid-3.5.25/src/main.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/MasterXaction.cc -o /data/download/squid/squid-3.5.25/src/MasterXaction.cc.bc
check
echo "441 /data/download/squid/squid-3.5.25/src/MasterXaction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/mem.cc -o /data/download/squid/squid-3.5.25/src/mem.cc.bc
check
echo "442 /data/download/squid/squid-3.5.25/src/mem.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/mem_node.cc -o /data/download/squid/squid-3.5.25/src/mem_node.cc.bc
check
echo "443 /data/download/squid/squid-3.5.25/src/mem_node.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/MemBuf.cc -o /data/download/squid/squid-3.5.25/src/MemBuf.cc.bc
check
echo "444 /data/download/squid/squid-3.5.25/src/MemBuf.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/MemObject.cc -o /data/download/squid/squid-3.5.25/src/MemObject.cc.bc
check
echo "445 /data/download/squid/squid-3.5.25/src/MemObject.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/mime.cc -o /data/download/squid/squid-3.5.25/src/mime.cc.bc
check
echo "446 /data/download/squid/squid-3.5.25/src/mime.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/mime_header.cc -o /data/download/squid/squid-3.5.25/src/mime_header.cc.bc
check
echo "447 /data/download/squid/squid-3.5.25/src/mime_header.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/multicast.cc -o /data/download/squid/squid-3.5.25/src/multicast.cc.bc
check
echo "448 /data/download/squid/squid-3.5.25/src/multicast.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/neighbors.cc -o /data/download/squid/squid-3.5.25/src/neighbors.cc.bc
check
echo "449 /data/download/squid/squid-3.5.25/src/neighbors.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/Notes.cc -o /data/download/squid/squid-3.5.25/src/Notes.cc.bc
check
echo "450 /data/download/squid/squid-3.5.25/src/Notes.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/Packer.cc -o /data/download/squid/squid-3.5.25/src/Packer.cc.bc
check
echo "451 /data/download/squid/squid-3.5.25/src/Packer.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/Parsing.cc -o /data/download/squid/squid-3.5.25/src/Parsing.cc.bc
check
echo "452 /data/download/squid/squid-3.5.25/src/Parsing.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/pconn.cc -o /data/download/squid/squid-3.5.25/src/pconn.cc.bc
check
echo "453 /data/download/squid/squid-3.5.25/src/pconn.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/peer_digest.cc -o /data/download/squid/squid-3.5.25/src/peer_digest.cc.bc
check
echo "454 /data/download/squid/squid-3.5.25/src/peer_digest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/peer_proxy_negotiate_auth.cc -o /data/download/squid/squid-3.5.25/src/peer_proxy_negotiate_auth.cc.bc
check
echo "455 /data/download/squid/squid-3.5.25/src/peer_proxy_negotiate_auth.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/peer_select.cc -o /data/download/squid/squid-3.5.25/src/peer_select.cc.bc
check
echo "456 /data/download/squid/squid-3.5.25/src/peer_select.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/peer_sourcehash.cc -o /data/download/squid/squid-3.5.25/src/peer_sourcehash.cc.bc
check
echo "457 /data/download/squid/squid-3.5.25/src/peer_sourcehash.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/peer_userhash.cc -o /data/download/squid/squid-3.5.25/src/peer_userhash.cc.bc
check
echo "458 /data/download/squid/squid-3.5.25/src/peer_userhash.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/PeerPoolMgr.cc -o /data/download/squid/squid-3.5.25/src/PeerPoolMgr.cc.bc
check
echo "459 /data/download/squid/squid-3.5.25/src/PeerPoolMgr.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/redirect.cc -o /data/download/squid/squid-3.5.25/src/redirect.cc.bc
check
echo "460 /data/download/squid/squid-3.5.25/src/redirect.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/refresh.cc -o /data/download/squid/squid-3.5.25/src/refresh.cc.bc
check
echo "461 /data/download/squid/squid-3.5.25/src/refresh.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/RemovalPolicy.cc -o /data/download/squid/squid-3.5.25/src/RemovalPolicy.cc.bc
check
echo "462 /data/download/squid/squid-3.5.25/src/RemovalPolicy.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/send-announce.cc -o /data/download/squid/squid-3.5.25/src/send-announce.cc.bc
check
echo "463 /data/download/squid/squid-3.5.25/src/send-announce.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/MemBlob.cc -o /data/download/squid/squid-3.5.25/src/MemBlob.cc.bc
check
echo "464 /data/download/squid/squid-3.5.25/src/MemBlob.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/SBuf.cc -o /data/download/squid/squid-3.5.25/src/SBuf.cc.bc
check
echo "465 /data/download/squid/squid-3.5.25/src/SBuf.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/SBufExceptions.cc -o /data/download/squid/squid-3.5.25/src/SBufExceptions.cc.bc
check
echo "466 /data/download/squid/squid-3.5.25/src/SBufExceptions.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/SBufDetailedStats.cc -o /data/download/squid/squid-3.5.25/src/SBufDetailedStats.cc.bc
check
echo "467 /data/download/squid/squid-3.5.25/src/SBufDetailedStats.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/SBufStatsAction.cc -o /data/download/squid/squid-3.5.25/src/SBufStatsAction.cc.bc
check
echo "468 /data/download/squid/squid-3.5.25/src/SBufStatsAction.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/snmp_core.cc -o /data/download/squid/squid-3.5.25/src/snmp_core.cc.bc
check
echo "469 /data/download/squid/squid-3.5.25/src/snmp_core.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/snmp_agent.cc -o /data/download/squid/squid-3.5.25/src/snmp_agent.cc.bc
check
echo "470 /data/download/squid/squid-3.5.25/src/snmp_agent.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/SquidMath.cc -o /data/download/squid/squid-3.5.25/src/SquidMath.cc.bc
check
echo "471 /data/download/squid/squid-3.5.25/src/SquidMath.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/SquidNew.cc -o /data/download/squid/squid-3.5.25/src/SquidNew.cc.bc
check
echo "472 /data/download/squid/squid-3.5.25/src/SquidNew.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/stat.cc -o /data/download/squid/squid-3.5.25/src/stat.cc.bc
check
echo "473 /data/download/squid/squid-3.5.25/src/stat.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StatCounters.cc -o /data/download/squid/squid-3.5.25/src/StatCounters.cc.bc
check
echo "474 /data/download/squid/squid-3.5.25/src/StatCounters.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StatHist.cc -o /data/download/squid/squid-3.5.25/src/StatHist.cc.bc
check
echo "475 /data/download/squid/squid-3.5.25/src/StatHist.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/String.cc -o /data/download/squid/squid-3.5.25/src/String.cc.bc
check
echo "476 /data/download/squid/squid-3.5.25/src/String.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StrList.cc -o /data/download/squid/squid-3.5.25/src/StrList.cc.bc
check
echo "477 /data/download/squid/squid-3.5.25/src/StrList.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/stmem.cc -o /data/download/squid/squid-3.5.25/src/stmem.cc.bc
check
echo "478 /data/download/squid/squid-3.5.25/src/stmem.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store.cc -o /data/download/squid/squid-3.5.25/src/store.cc.bc
check
echo "479 /data/download/squid/squid-3.5.25/src/store.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreFileSystem.cc -o /data/download/squid/squid-3.5.25/src/StoreFileSystem.cc.bc
check
echo "480 /data/download/squid/squid-3.5.25/src/StoreFileSystem.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store_io.cc -o /data/download/squid/squid-3.5.25/src/store_io.cc.bc
check
echo "481 /data/download/squid/squid-3.5.25/src/store_io.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreIOState.cc -o /data/download/squid/squid-3.5.25/src/StoreIOState.cc.bc
check
echo "482 /data/download/squid/squid-3.5.25/src/StoreIOState.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store_client.cc -o /data/download/squid/squid-3.5.25/src/store_client.cc.bc
check
echo "483 /data/download/squid/squid-3.5.25/src/store_client.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store_digest.cc -o /data/download/squid/squid-3.5.25/src/store_digest.cc.bc
check
echo "484 /data/download/squid/squid-3.5.25/src/store_digest.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store_dir.cc -o /data/download/squid/squid-3.5.25/src/store_dir.cc.bc
check
echo "485 /data/download/squid/squid-3.5.25/src/store_dir.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store_key_md5.cc -o /data/download/squid/squid-3.5.25/src/store_key_md5.cc.bc
check
echo "486 /data/download/squid/squid-3.5.25/src/store_key_md5.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store_log.cc -o /data/download/squid/squid-3.5.25/src/store_log.cc.bc
check
echo "487 /data/download/squid/squid-3.5.25/src/store_log.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store_rebuild.cc -o /data/download/squid/squid-3.5.25/src/store_rebuild.cc.bc
check
echo "488 /data/download/squid/squid-3.5.25/src/store_rebuild.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store_swapin.cc -o /data/download/squid/squid-3.5.25/src/store_swapin.cc.bc
check
echo "489 /data/download/squid/squid-3.5.25/src/store_swapin.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store_swapmeta.cc -o /data/download/squid/squid-3.5.25/src/store_swapmeta.cc.bc
check
echo "490 /data/download/squid/squid-3.5.25/src/store_swapmeta.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/store_swapout.cc -o /data/download/squid/squid-3.5.25/src/store_swapout.cc.bc
check
echo "491 /data/download/squid/squid-3.5.25/src/store_swapout.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreMetaUnpacker.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaUnpacker.cc.bc
check
echo "492 /data/download/squid/squid-3.5.25/src/StoreMetaUnpacker.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreMeta.cc -o /data/download/squid/squid-3.5.25/src/StoreMeta.cc.bc
check
echo "493 /data/download/squid/squid-3.5.25/src/StoreMeta.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreMetaMD5.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaMD5.cc.bc
check
echo "494 /data/download/squid/squid-3.5.25/src/StoreMetaMD5.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreMetaSTD.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaSTD.cc.bc
check
echo "495 /data/download/squid/squid-3.5.25/src/StoreMetaSTD.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreMetaSTDLFS.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaSTDLFS.cc.bc
check
echo "496 /data/download/squid/squid-3.5.25/src/StoreMetaSTDLFS.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreMetaURL.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaURL.cc.bc
check
echo "497 /data/download/squid/squid-3.5.25/src/StoreMetaURL.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreMetaVary.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaVary.cc.bc
check
echo "498 /data/download/squid/squid-3.5.25/src/StoreMetaVary.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreStats.cc -o /data/download/squid/squid-3.5.25/src/StoreStats.cc.bc
check
echo "499 /data/download/squid/squid-3.5.25/src/StoreStats.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/StoreSwapLogData.cc -o /data/download/squid/squid-3.5.25/src/StoreSwapLogData.cc.bc
check
echo "500 /data/download/squid/squid-3.5.25/src/StoreSwapLogData.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/SwapDir.cc -o /data/download/squid/squid-3.5.25/src/SwapDir.cc.bc
check
echo "501 /data/download/squid/squid-3.5.25/src/SwapDir.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/Transients.cc -o /data/download/squid/squid-3.5.25/src/Transients.cc.bc
check
echo "502 /data/download/squid/squid-3.5.25/src/Transients.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/MemStore.cc -o /data/download/squid/squid-3.5.25/src/MemStore.cc.bc
check
echo "503 /data/download/squid/squid-3.5.25/src/MemStore.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/tools.cc -o /data/download/squid/squid-3.5.25/src/tools.cc.bc
check
echo "504 /data/download/squid/squid-3.5.25/src/tools.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/tunnel.cc -o /data/download/squid/squid-3.5.25/src/tunnel.cc.bc
check
echo "505 /data/download/squid/squid-3.5.25/src/tunnel.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/unlinkd.cc -o /data/download/squid/squid-3.5.25/src/unlinkd.cc.bc
check
echo "506 /data/download/squid/squid-3.5.25/src/unlinkd.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/url.cc -o /data/download/squid/squid-3.5.25/src/url.cc.bc
check
echo "507 /data/download/squid/squid-3.5.25/src/url.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/urn.cc -o /data/download/squid/squid-3.5.25/src/urn.cc.bc
check
echo "508 /data/download/squid/squid-3.5.25/src/urn.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/wccp.cc -o /data/download/squid/squid-3.5.25/src/wccp.cc.bc
check
echo "509 /data/download/squid/squid-3.5.25/src/wccp.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/wccp2.cc -o /data/download/squid/squid-3.5.25/src/wccp2.cc.bc
check
echo "510 /data/download/squid/squid-3.5.25/src/wccp2.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/whois.cc -o /data/download/squid/squid-3.5.25/src/whois.cc.bc
check
echo "511 /data/download/squid/squid-3.5.25/src/whois.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/wordlist.cc -o /data/download/squid/squid-3.5.25/src/wordlist.cc.bc
check
echo "512 /data/download/squid/squid-3.5.25/src/wordlist.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/LoadableModule.cc -o /data/download/squid/squid-3.5.25/src/LoadableModule.cc.bc
check
echo "513 /data/download/squid/squid-3.5.25/src/LoadableModule.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/LoadableModules.cc -o /data/download/squid/squid-3.5.25/src/LoadableModules.cc.bc
check
echo "514 /data/download/squid/squid-3.5.25/src/LoadableModules.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModules_gen.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModules_gen.cc.bc
check
echo "515 /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModules_gen.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/err_type.cc -o /data/download/squid/squid-3.5.25/src/err_type.cc.bc
check
echo "516 /data/download/squid/squid-3.5.25/src/err_type.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/err_detail_type.cc -o /data/download/squid/squid-3.5.25/src/err_detail_type.cc.bc
check
echo "517 /data/download/squid/squid-3.5.25/src/err_detail_type.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/globals.cc -o /data/download/squid/squid-3.5.25/src/globals.cc.bc
check
echo "518 /data/download/squid/squid-3.5.25/src/globals.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/hier_code.cc -o /data/download/squid/squid-3.5.25/src/hier_code.cc.bc
check
echo "519 /data/download/squid/squid-3.5.25/src/hier_code.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/icp_opcode.cc -o /data/download/squid/squid-3.5.25/src/icp_opcode.cc.bc
check
echo "520 /data/download/squid/squid-3.5.25/src/icp_opcode.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/LogTags.cc -o /data/download/squid/squid-3.5.25/src/LogTags.cc.bc
check
echo "521 /data/download/squid/squid-3.5.25/src/LogTags.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/lookup_t.cc -o /data/download/squid/squid-3.5.25/src/lookup_t.cc.bc
check
echo "522 /data/download/squid/squid-3.5.25/src/lookup_t.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/repl_modules.cc -o /data/download/squid/squid-3.5.25/src/repl_modules.cc.bc
check
echo "523 /data/download/squid/squid-3.5.25/src/repl_modules.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -c /data/download/squid/squid-3.5.25/src/swap_log_op.cc -o /data/download/squid/squid-3.5.25/src/swap_log_op.cc.bc
check
echo "524 /data/download/squid/squid-3.5.25/src/swap_log_op.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/src/.libs
clang -g -emit-llvm -c /data/download/squid/squid-3.5.25/src/.libs/squidS.c -o /data/download/squid/squid-3.5.25/src/.libs/squidS.c.bc
check
echo "525 /data/download/squid/squid-3.5.25/src/.libs/squidS.c to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/purge/convert.cc -o /data/download/squid/squid-3.5.25/tools/purge/convert.cc.bc
check
echo "526 /data/download/squid/squid-3.5.25/tools/purge/convert.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/purge/socket.cc -o /data/download/squid/squid-3.5.25/tools/purge/socket.cc.bc
check
echo "527 /data/download/squid/squid-3.5.25/tools/purge/socket.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/purge/signal.cc -o /data/download/squid/squid-3.5.25/tools/purge/signal.cc.bc
check
echo "528 /data/download/squid/squid-3.5.25/tools/purge/signal.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/purge/squid-tlv.cc -o /data/download/squid/squid-3.5.25/tools/purge/squid-tlv.cc.bc
check
echo "529 /data/download/squid/squid-3.5.25/tools/purge/squid-tlv.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/purge/copyout.cc -o /data/download/squid/squid-3.5.25/tools/purge/copyout.cc.bc
check
echo "530 /data/download/squid/squid-3.5.25/tools/purge/copyout.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/purge/conffile.cc -o /data/download/squid/squid-3.5.25/tools/purge/conffile.cc.bc
check
echo "531 /data/download/squid/squid-3.5.25/tools/purge/conffile.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/purge/purge.cc -o /data/download/squid/squid-3.5.25/tools/purge/purge.cc.bc
check
echo "532 /data/download/squid/squid-3.5.25/tools/purge/purge.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/squidclient/gssapi_support.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/gssapi_support.cc.bc
check
echo "533 /data/download/squid/squid-3.5.25/tools/squidclient/gssapi_support.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/squidclient/Ping.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/Ping.cc.bc
check
echo "534 /data/download/squid/squid-3.5.25/tools/squidclient/Ping.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/squidclient/squidclient.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/squidclient.cc.bc
check
echo "535 /data/download/squid/squid-3.5.25/tools/squidclient/squidclient.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/squidclient/stub_debug.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/stub_debug.cc.bc
check
echo "536 /data/download/squid/squid-3.5.25/tools/squidclient/stub_debug.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/squidclient/test_tools.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/test_tools.cc.bc
check
echo "537 /data/download/squid/squid-3.5.25/tools/squidclient/test_tools.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/squidclient/time.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/time.cc.bc
check
echo "538 /data/download/squid/squid-3.5.25/tools/squidclient/time.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/squidclient/Transport.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/Transport.cc.bc
check
echo "539 /data/download/squid/squid-3.5.25/tools/squidclient/Transport.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/cachemgr.cc -o /data/download/squid/squid-3.5.25/tools/cachemgr.cc.bc
check
echo "540 /data/download/squid/squid-3.5.25/tools/cachemgr.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/MemBuf.cc -o /data/download/squid/squid-3.5.25/tools/MemBuf.cc.bc
check
echo "541 /data/download/squid/squid-3.5.25/tools/MemBuf.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/stub_cbdata.cc -o /data/download/squid/squid-3.5.25/tools/stub_cbdata.cc.bc
check
echo "542 /data/download/squid/squid-3.5.25/tools/stub_cbdata.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/stub_debug.cc -o /data/download/squid/squid-3.5.25/tools/stub_debug.cc.bc
check
echo "543 /data/download/squid/squid-3.5.25/tools/stub_debug.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/stub_mem.cc -o /data/download/squid/squid-3.5.25/tools/stub_mem.cc.bc
check
echo "544 /data/download/squid/squid-3.5.25/tools/stub_mem.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/test_tools.cc -o /data/download/squid/squid-3.5.25/tools/test_tools.cc.bc
check
echo "545 /data/download/squid/squid-3.5.25/tools/test_tools.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -c /data/download/squid/squid-3.5.25/tools/time.cc -o /data/download/squid/squid-3.5.25/tools/time.cc.bc
check
echo "546 /data/download/squid/squid-3.5.25/tools/time.cc to bc" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/assert.cc -o /data/download/squid/squid-3.5.25/compat/assert.cc.ll
echo "1 /data/download/squid/squid-3.5.25/compat/assert.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/compat.cc -o /data/download/squid/squid-3.5.25/compat/compat.cc.ll
echo "2 /data/download/squid/squid-3.5.25/compat/compat.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/debug.cc -o /data/download/squid/squid-3.5.25/compat/debug.cc.ll
echo "3 /data/download/squid/squid-3.5.25/compat/debug.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/eui64_aton.c -o /data/download/squid/squid-3.5.25/compat/eui64_aton.c.ll
echo "4 /data/download/squid/squid-3.5.25/compat/eui64_aton.c to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/getaddrinfo.cc -o /data/download/squid/squid-3.5.25/compat/getaddrinfo.cc.ll
echo "5 /data/download/squid/squid-3.5.25/compat/getaddrinfo.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/getnameinfo.cc -o /data/download/squid/squid-3.5.25/compat/getnameinfo.cc.ll
echo "6 /data/download/squid/squid-3.5.25/compat/getnameinfo.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/GnuRegex.c -o /data/download/squid/squid-3.5.25/compat/GnuRegex.c.ll
echo "7 /data/download/squid/squid-3.5.25/compat/GnuRegex.c to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/inet_ntop.cc -o /data/download/squid/squid-3.5.25/compat/inet_ntop.cc.ll
echo "8 /data/download/squid/squid-3.5.25/compat/inet_ntop.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/inet_pton.cc -o /data/download/squid/squid-3.5.25/compat/inet_pton.cc.ll
echo "9 /data/download/squid/squid-3.5.25/compat/inet_pton.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/memrchr.cc -o /data/download/squid/squid-3.5.25/compat/memrchr.cc.ll
echo "10 /data/download/squid/squid-3.5.25/compat/memrchr.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/shm.cc -o /data/download/squid/squid-3.5.25/compat/shm.cc.ll
echo "11 /data/download/squid/squid-3.5.25/compat/shm.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/statvfs.cc -o /data/download/squid/squid-3.5.25/compat/statvfs.cc.ll
echo "12 /data/download/squid/squid-3.5.25/compat/statvfs.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/strnstr.cc -o /data/download/squid/squid-3.5.25/compat/strnstr.cc.ll
echo "13 /data/download/squid/squid-3.5.25/compat/strnstr.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/strnrchr.c -o /data/download/squid/squid-3.5.25/compat/strnrchr.c.ll
echo "14 /data/download/squid/squid-3.5.25/compat/strnrchr.c to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/xalloc.cc -o /data/download/squid/squid-3.5.25/compat/xalloc.cc.ll
echo "15 /data/download/squid/squid-3.5.25/compat/xalloc.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/xstrerror.cc -o /data/download/squid/squid-3.5.25/compat/xstrerror.cc.ll
echo "16 /data/download/squid/squid-3.5.25/compat/xstrerror.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/xstring.cc -o /data/download/squid/squid-3.5.25/compat/xstring.cc.ll
echo "17 /data/download/squid/squid-3.5.25/compat/xstring.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/xstrto.cc -o /data/download/squid/squid-3.5.25/compat/xstrto.cc.ll
echo "18 /data/download/squid/squid-3.5.25/compat/xstrto.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/compat
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/compat/mswindows.cc -o /data/download/squid/squid-3.5.25/compat/mswindows.cc.ll
echo "19 /data/download/squid/squid-3.5.25/compat/mswindows.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/asn1.c -o /data/download/squid/squid-3.5.25/lib/snmplib/asn1.c.ll
echo "20 /data/download/squid/squid-3.5.25/lib/snmplib/asn1.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/parse.c -o /data/download/squid/squid-3.5.25/lib/snmplib/parse.c.ll
echo "21 /data/download/squid/squid-3.5.25/lib/snmplib/parse.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/snmp_vars.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_vars.c.ll
echo "22 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_vars.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/coexistance.c -o /data/download/squid/squid-3.5.25/lib/snmplib/coexistance.c.ll
echo "23 /data/download/squid/squid-3.5.25/lib/snmplib/coexistance.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api.c.ll
echo "24 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/snmp_error.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_error.c.ll
echo "25 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_error.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/mib.c -o /data/download/squid/squid-3.5.25/lib/snmplib/mib.c.ll
echo "26 /data/download/squid/squid-3.5.25/lib/snmplib/mib.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api_error.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api_error.c.ll
echo "27 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_api_error.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/snmp_msg.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_msg.c.ll
echo "28 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_msg.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/snmp_pdu.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmp_pdu.c.ll
echo "29 /data/download/squid/squid-3.5.25/lib/snmplib/snmp_pdu.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/snmplib
clang -g -emit-llvm -DSQUID_SNMP=1 -I../.. -I../../include -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/snmplib/snmplib_debug.c -o /data/download/squid/squid-3.5.25/lib/snmplib/snmplib_debug.c.ll
echo "30 /data/download/squid/squid-3.5.25/lib/snmplib/snmplib_debug.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/rfcnb
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-io.c -o /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-io.c.ll
echo "31 /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-io.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/rfcnb
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-util.c -o /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-util.c.ll
echo "32 /data/download/squid/squid-3.5.25/lib/rfcnb/rfcnb-util.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/rfcnb
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/rfcnb/session.c -o /data/download/squid/squid-3.5.25/lib/rfcnb/session.c.ll
echo "33 /data/download/squid/squid-3.5.25/lib/rfcnb/session.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/smblib
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/smblib/md4.c -o /data/download/squid/squid-3.5.25/lib/smblib/md4.c.ll
echo "34 /data/download/squid/squid-3.5.25/lib/smblib/md4.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/smblib
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/smblib/smblib.c -o /data/download/squid/squid-3.5.25/lib/smblib/smblib.c.ll
echo "35 /data/download/squid/squid-3.5.25/lib/smblib/smblib.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/smblib
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/smblib/smblib-util.c -o /data/download/squid/squid-3.5.25/lib/smblib/smblib-util.c.ll
echo "36 /data/download/squid/squid-3.5.25/lib/smblib/smblib-util.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/smblib
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/smblib/smbencrypt.c -o /data/download/squid/squid-3.5.25/lib/smblib/smbencrypt.c.ll
echo "37 /data/download/squid/squid-3.5.25/lib/smblib/smbencrypt.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/smblib
clang -g -emit-llvm -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/smblib/smbdes.c -o /data/download/squid/squid-3.5.25/lib/smblib/smbdes.c.ll
echo "38 /data/download/squid/squid-3.5.25/lib/smblib/smbdes.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib/ntlmauth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I../../lib -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/ntlmauth/ntlmauth.cc -o /data/download/squid/squid-3.5.25/lib/ntlmauth/ntlmauth.cc.ll
echo "39 /data/download/squid/squid-3.5.25/lib/ntlmauth/ntlmauth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/base64.c -o /data/download/squid/squid-3.5.25/lib/base64.c.ll
echo "40 /data/download/squid/squid-3.5.25/lib/base64.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/charset.c -o /data/download/squid/squid-3.5.25/lib/charset.c.ll
echo "41 /data/download/squid/squid-3.5.25/lib/charset.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/html_quote.c -o /data/download/squid/squid-3.5.25/lib/html_quote.c.ll
echo "42 /data/download/squid/squid-3.5.25/lib/html_quote.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/md5.c -o /data/download/squid/squid-3.5.25/lib/md5.c.ll
echo "43 /data/download/squid/squid-3.5.25/lib/md5.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/rfc1738.c -o /data/download/squid/squid-3.5.25/lib/rfc1738.c.ll
echo "44 /data/download/squid/squid-3.5.25/lib/rfc1738.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/rfc2617.c -o /data/download/squid/squid-3.5.25/lib/rfc2617.c.ll
echo "45 /data/download/squid/squid-3.5.25/lib/rfc2617.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/uudecode.c -o /data/download/squid/squid-3.5.25/lib/uudecode.c.ll
echo "46 /data/download/squid/squid-3.5.25/lib/uudecode.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/hash.cc -o /data/download/squid/squid-3.5.25/lib/hash.cc.ll
echo "47 /data/download/squid/squid-3.5.25/lib/hash.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/MemPool.cc -o /data/download/squid/squid-3.5.25/lib/MemPool.cc.ll
echo "48 /data/download/squid/squid-3.5.25/lib/MemPool.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/MemPoolChunked.cc -o /data/download/squid/squid-3.5.25/lib/MemPoolChunked.cc.ll
echo "49 /data/download/squid/squid-3.5.25/lib/MemPoolChunked.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/MemPoolMalloc.cc -o /data/download/squid/squid-3.5.25/lib/MemPoolMalloc.cc.ll
echo "50 /data/download/squid/squid-3.5.25/lib/MemPoolMalloc.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/getfullhostname.c -o /data/download/squid/squid-3.5.25/lib/getfullhostname.c.ll
echo "51 /data/download/squid/squid-3.5.25/lib/getfullhostname.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/heap.c -o /data/download/squid/squid-3.5.25/lib/heap.c.ll
echo "52 /data/download/squid/squid-3.5.25/lib/heap.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/iso3307.c -o /data/download/squid/squid-3.5.25/lib/iso3307.c.ll
echo "53 /data/download/squid/squid-3.5.25/lib/iso3307.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/radix.c -o /data/download/squid/squid-3.5.25/lib/radix.c.ll
echo "54 /data/download/squid/squid-3.5.25/lib/radix.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/rfc1035.c -o /data/download/squid/squid-3.5.25/lib/rfc1035.c.ll
echo "55 /data/download/squid/squid-3.5.25/lib/rfc1035.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/rfc1123.c -o /data/download/squid/squid-3.5.25/lib/rfc1123.c.ll
echo "56 /data/download/squid/squid-3.5.25/lib/rfc1123.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/rfc2671.c -o /data/download/squid/squid-3.5.25/lib/rfc2671.c.ll
echo "57 /data/download/squid/squid-3.5.25/lib/rfc2671.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/rfc3596.c -o /data/download/squid/squid-3.5.25/lib/rfc3596.c.ll
echo "58 /data/download/squid/squid-3.5.25/lib/rfc3596.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/Splay.cc -o /data/download/squid/squid-3.5.25/lib/Splay.cc.ll
echo "59 /data/download/squid/squid-3.5.25/lib/Splay.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/stub_memaccount.c -o /data/download/squid/squid-3.5.25/lib/stub_memaccount.c.ll
echo "60 /data/download/squid/squid-3.5.25/lib/stub_memaccount.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/util.c -o /data/download/squid/squid-3.5.25/lib/util.c.ll
echo "61 /data/download/squid/squid-3.5.25/lib/util.c to ll" >&2

cd /data/download/squid/squid-3.5.25/lib
clang -g -emit-llvm -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/lib/xusleep.c -o /data/download/squid/squid-3.5.25/lib/xusleep.c.ll
echo "62 /data/download/squid/squid-3.5.25/lib/xusleep.c to ll" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -S /data/download/squid/squid-3.5.25/libltdl/loaders/dlopen.c -o /data/download/squid/squid-3.5.25/libltdl/loaders/dlopen.c.ll
echo "63 /data/download/squid/squid-3.5.25/libltdl/loaders/dlopen.c to ll" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -S /data/download/squid/squid-3.5.25/libltdl/loaders/preopen.c -o /data/download/squid/squid-3.5.25/libltdl/loaders/preopen.c.ll
echo "64 /data/download/squid/squid-3.5.25/libltdl/loaders/preopen.c to ll" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -S /data/download/squid/squid-3.5.25/libltdl/lt__alloc.c -o /data/download/squid/squid-3.5.25/libltdl/lt__alloc.c.ll
echo "65 /data/download/squid/squid-3.5.25/libltdl/lt__alloc.c to ll" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -S /data/download/squid/squid-3.5.25/libltdl/lt_dlloader.c -o /data/download/squid/squid-3.5.25/libltdl/lt_dlloader.c.ll
echo "66 /data/download/squid/squid-3.5.25/libltdl/lt_dlloader.c to ll" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -S /data/download/squid/squid-3.5.25/libltdl/lt_error.c -o /data/download/squid/squid-3.5.25/libltdl/lt_error.c.ll
echo "67 /data/download/squid/squid-3.5.25/libltdl/lt_error.c to ll" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -S /data/download/squid/squid-3.5.25/libltdl/ltdl.c -o /data/download/squid/squid-3.5.25/libltdl/ltdl.c.ll
echo "68 /data/download/squid/squid-3.5.25/libltdl/ltdl.c to ll" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLTDLOPEN=libltdlc -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -S /data/download/squid/squid-3.5.25/libltdl/slist.c -o /data/download/squid/squid-3.5.25/libltdl/slist.c.ll
echo "69 /data/download/squid/squid-3.5.25/libltdl/slist.c to ll" >&2

cd /data/download/squid/squid-3.5.25/libltdl
clang -g -emit-llvm -DHAVE_CONFIG_H -I. -DLT_CONFIG_H=<config.h> -DLTDL -I. -I. -Ilibltdl -I./libltdl -DPIC -S /data/download/squid/squid-3.5.25/libltdl/lt__strl.c -o /data/download/squid/squid-3.5.25/libltdl/lt__strl.c.ll
echo "70 /data/download/squid/squid-3.5.25/libltdl/lt__strl.c to ll" >&2

cd /data/download/squid/squid-3.5.25/libltdl/.libs
clang -g -emit-llvm -DPIC -S /data/download/squid/squid-3.5.25/libltdl/.libs/libltdlcS.c -o /data/download/squid/squid-3.5.25/libltdl/.libs/libltdlcS.c.ll
echo "71 /data/download/squid/squid-3.5.25/libltdl/.libs/libltdlcS.c to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/basic_ncsa_auth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/basic_ncsa_auth.cc.ll
echo "72 /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/basic_ncsa_auth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/crypt_md5.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/crypt_md5.cc.ll
echo "73 /data/download/squid/squid-3.5.25/helpers/basic_auth/NCSA/crypt_md5.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/basic_nis_auth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/basic_nis_auth.cc.ll
echo "74 /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/basic_nis_auth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/nis_support.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/nis_support.cc.ll
echo "75 /data/download/squid/squid-3.5.25/helpers/basic_auth/NIS/nis_support.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/basic_radius_auth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/basic_radius_auth.cc.ll
echo "76 /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/basic_radius_auth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/radius-util.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/radius-util.cc.ll
echo "77 /data/download/squid/squid-3.5.25/helpers/basic_auth/RADIUS/radius-util.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -DHELPERSCRIPT=\"/usr/local/squid/libexec/basic_smb_auth.sh\" -S /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB/basic_smb_auth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB/basic_smb_auth.cc.ll
echo "78 /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB/basic_smb_auth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -I../../../lib -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/msntauth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/msntauth.cc.ll
echo "79 /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/msntauth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -I../../../lib -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/valid.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/valid.cc.ll
echo "80 /data/download/squid/squid-3.5.25/helpers/basic_auth/SMB_LM/valid.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/fake
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/basic_auth/fake/fake.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/fake/fake.cc.ll
echo "81 /data/download/squid/squid-3.5.25/helpers/basic_auth/fake/fake.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/basic_auth/getpwnam
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/basic_auth/getpwnam/basic_getpwnam_auth.cc -o /data/download/squid/squid-3.5.25/helpers/basic_auth/getpwnam/basic_getpwnam_auth.cc.ll
echo "82 /data/download/squid/squid-3.5.25/helpers/basic_auth/getpwnam/basic_getpwnam_auth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/digest_auth/file
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/digest_auth/file/digest_file_auth.cc -o /data/download/squid/squid-3.5.25/helpers/digest_auth/file/digest_file_auth.cc.ll
echo "83 /data/download/squid/squid-3.5.25/helpers/digest_auth/file/digest_file_auth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/digest_auth/file
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I. -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/digest_auth/file/text_backend.cc -o /data/download/squid/squid-3.5.25/helpers/digest_auth/file/text_backend.cc.ll
echo "84 /data/download/squid/squid-3.5.25/helpers/digest_auth/file/text_backend.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/external_acl/file_userip
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/external_acl/file_userip/ext_file_userip_acl.cc -o /data/download/squid/squid-3.5.25/helpers/external_acl/file_userip/ext_file_userip_acl.cc.ll
echo "85 /data/download/squid/squid-3.5.25/helpers/external_acl/file_userip/ext_file_userip_acl.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/external_acl/unix_group
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/external_acl/unix_group/check_group.cc -o /data/download/squid/squid-3.5.25/helpers/external_acl/unix_group/check_group.cc.ll
echo "86 /data/download/squid/squid-3.5.25/helpers/external_acl/unix_group/check_group.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/log_daemon/file
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/log_daemon/file/log_file_daemon.cc -o /data/download/squid/squid-3.5.25/helpers/log_daemon/file/log_file_daemon.cc.ll
echo "87 /data/download/squid/squid-3.5.25/helpers/log_daemon/file/log_file_daemon.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/negotiate_auth/wrapper
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/negotiate_auth/wrapper/negotiate_wrapper.cc -o /data/download/squid/squid-3.5.25/helpers/negotiate_auth/wrapper/negotiate_wrapper.cc.ll
echo "88 /data/download/squid/squid-3.5.25/helpers/negotiate_auth/wrapper/negotiate_wrapper.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/url_rewrite/fake
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/url_rewrite/fake/fake.cc -o /data/download/squid/squid-3.5.25/helpers/url_rewrite/fake/fake.cc.ll
echo "89 /data/download/squid/squid-3.5.25/helpers/url_rewrite/fake/fake.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/ntlm_auth/fake
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I../../../lib -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/ntlm_auth/fake/ntlm_fake_auth.cc -o /data/download/squid/squid-3.5.25/helpers/ntlm_auth/fake/ntlm_fake_auth.cc.ll
echo "90 /data/download/squid/squid-3.5.25/helpers/ntlm_auth/fake/ntlm_fake_auth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/helpers/ntlm_auth/smb_lm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -I../../../lib -D_REENTRANT -S /data/download/squid/squid-3.5.25/helpers/ntlm_auth/smb_lm/ntlm_smb_lm_auth.cc -o /data/download/squid/squid-3.5.25/helpers/ntlm_auth/smb_lm/ntlm_smb_lm_auth.cc.ll
echo "91 /data/download/squid/squid-3.5.25/helpers/ntlm_auth/smb_lm/ntlm_smb_lm_auth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -I. -I../include/ -I../src", -S /data/download/squid/squid-3.5.25/src/./cf_gen.cc -o /data/download/squid/squid-3.5.25/src/./cf_gen.cc.ll
echo "92 /data/download/squid/squid-3.5.25/src/./cf_gen.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/base/AsyncCall.cc -o /data/download/squid/squid-3.5.25/src/base/AsyncCall.cc.ll
echo "93 /data/download/squid/squid-3.5.25/src/base/AsyncCall.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/base/AsyncJob.cc -o /data/download/squid/squid-3.5.25/src/base/AsyncJob.cc.ll
echo "94 /data/download/squid/squid-3.5.25/src/base/AsyncJob.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/base/AsyncCallQueue.cc -o /data/download/squid/squid-3.5.25/src/base/AsyncCallQueue.cc.ll
echo "95 /data/download/squid/squid-3.5.25/src/base/AsyncCallQueue.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/base/CharacterSet.cc -o /data/download/squid/squid-3.5.25/src/base/CharacterSet.cc.ll
echo "96 /data/download/squid/squid-3.5.25/src/base/CharacterSet.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/base/RunnersRegistry.cc -o /data/download/squid/squid-3.5.25/src/base/RunnersRegistry.cc.ll
echo "97 /data/download/squid/squid-3.5.25/src/base/RunnersRegistry.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/base
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/base/TextException.cc -o /data/download/squid/squid-3.5.25/src/base/TextException.cc.ll
echo "98 /data/download/squid/squid-3.5.25/src/base/TextException.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/anyp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/anyp/PortCfg.cc -o /data/download/squid/squid-3.5.25/src/anyp/PortCfg.cc.ll
echo "99 /data/download/squid/squid-3.5.25/src/anyp/PortCfg.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/anyp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/anyp/ProtocolType.cc -o /data/download/squid/squid-3.5.25/src/anyp/ProtocolType.cc.ll
echo "100 /data/download/squid/squid-3.5.25/src/anyp/ProtocolType.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/anyp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/anyp/UriScheme.cc -o /data/download/squid/squid-3.5.25/src/anyp/UriScheme.cc.ll
echo "101 /data/download/squid/squid-3.5.25/src/anyp/UriScheme.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/helper
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/helper/ChildConfig.cc -o /data/download/squid/squid-3.5.25/src/helper/ChildConfig.cc.ll
echo "102 /data/download/squid/squid-3.5.25/src/helper/ChildConfig.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/helper
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/helper/Reply.cc -o /data/download/squid/squid-3.5.25/src/helper/Reply.cc.ll
echo "103 /data/download/squid/squid-3.5.25/src/helper/Reply.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ftp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ftp/Elements.cc -o /data/download/squid/squid-3.5.25/src/ftp/Elements.cc.ll
echo "104 /data/download/squid/squid-3.5.25/src/ftp/Elements.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ftp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ftp/Parsing.cc -o /data/download/squid/squid-3.5.25/src/ftp/Parsing.cc.ll
echo "105 /data/download/squid/squid-3.5.25/src/ftp/Parsing.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/parser
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/parser/Tokenizer.cc -o /data/download/squid/squid-3.5.25/src/parser/Tokenizer.cc.ll
echo "106 /data/download/squid/squid-3.5.25/src/parser/Tokenizer.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/AcceptLimiter.cc -o /data/download/squid/squid-3.5.25/src/comm/AcceptLimiter.cc.ll
echo "107 /data/download/squid/squid-3.5.25/src/comm/AcceptLimiter.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/ConnOpener.cc -o /data/download/squid/squid-3.5.25/src/comm/ConnOpener.cc.ll
echo "108 /data/download/squid/squid-3.5.25/src/comm/ConnOpener.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/Connection.cc -o /data/download/squid/squid-3.5.25/src/comm/Connection.cc.ll
echo "109 /data/download/squid/squid-3.5.25/src/comm/Connection.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/IoCallback.cc -o /data/download/squid/squid-3.5.25/src/comm/IoCallback.cc.ll
echo "110 /data/download/squid/squid-3.5.25/src/comm/IoCallback.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/ModDevPoll.cc -o /data/download/squid/squid-3.5.25/src/comm/ModDevPoll.cc.ll
echo "111 /data/download/squid/squid-3.5.25/src/comm/ModDevPoll.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/ModEpoll.cc -o /data/download/squid/squid-3.5.25/src/comm/ModEpoll.cc.ll
echo "112 /data/download/squid/squid-3.5.25/src/comm/ModEpoll.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/ModKqueue.cc -o /data/download/squid/squid-3.5.25/src/comm/ModKqueue.cc.ll
echo "113 /data/download/squid/squid-3.5.25/src/comm/ModKqueue.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/ModPoll.cc -o /data/download/squid/squid-3.5.25/src/comm/ModPoll.cc.ll
echo "114 /data/download/squid/squid-3.5.25/src/comm/ModPoll.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/ModSelect.cc -o /data/download/squid/squid-3.5.25/src/comm/ModSelect.cc.ll
echo "115 /data/download/squid/squid-3.5.25/src/comm/ModSelect.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/ModSelectWin32.cc -o /data/download/squid/squid-3.5.25/src/comm/ModSelectWin32.cc.ll
echo "116 /data/download/squid/squid-3.5.25/src/comm/ModSelectWin32.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/Read.cc -o /data/download/squid/squid-3.5.25/src/comm/Read.cc.ll
echo "117 /data/download/squid/squid-3.5.25/src/comm/Read.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/TcpAcceptor.cc -o /data/download/squid/squid-3.5.25/src/comm/TcpAcceptor.cc.ll
echo "118 /data/download/squid/squid-3.5.25/src/comm/TcpAcceptor.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/comm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm/Write.cc -o /data/download/squid/squid-3.5.25/src/comm/Write.cc.ll
echo "119 /data/download/squid/squid-3.5.25/src/comm/Write.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/eui
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/eui/Config.cc -o /data/download/squid/squid-3.5.25/src/eui/Config.cc.ll
echo "120 /data/download/squid/squid-3.5.25/src/eui/Config.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/eui
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/eui/Eui48.cc -o /data/download/squid/squid-3.5.25/src/eui/Eui48.cc.ll
echo "121 /data/download/squid/squid-3.5.25/src/eui/Eui48.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/eui
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/eui/Eui64.cc -o /data/download/squid/squid-3.5.25/src/eui/Eui64.cc.ll
echo "122 /data/download/squid/squid-3.5.25/src/eui/Eui64.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Acl.cc -o /data/download/squid/squid-3.5.25/src/acl/Acl.cc.ll
echo "123 /data/download/squid/squid-3.5.25/src/acl/Acl.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/BoolOps.cc -o /data/download/squid/squid-3.5.25/src/acl/BoolOps.cc.ll
echo "124 /data/download/squid/squid-3.5.25/src/acl/BoolOps.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Checklist.cc -o /data/download/squid/squid-3.5.25/src/acl/Checklist.cc.ll
echo "125 /data/download/squid/squid-3.5.25/src/acl/Checklist.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/InnerNode.cc -o /data/download/squid/squid-3.5.25/src/acl/InnerNode.cc.ll
echo "126 /data/download/squid/squid-3.5.25/src/acl/InnerNode.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Tree.cc -o /data/download/squid/squid-3.5.25/src/acl/Tree.cc.ll
echo "127 /data/download/squid/squid-3.5.25/src/acl/Tree.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Strategised.cc -o /data/download/squid/squid-3.5.25/src/acl/Strategised.cc.ll
echo "128 /data/download/squid/squid-3.5.25/src/acl/Strategised.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/FilledChecklist.cc -o /data/download/squid/squid-3.5.25/src/acl/FilledChecklist.cc.ll
echo "129 /data/download/squid/squid-3.5.25/src/acl/FilledChecklist.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/AclAddress.cc -o /data/download/squid/squid-3.5.25/src/acl/AclAddress.cc.ll
echo "130 /data/download/squid/squid-3.5.25/src/acl/AclAddress.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/IntRange.cc -o /data/download/squid/squid-3.5.25/src/acl/IntRange.cc.ll
echo "131 /data/download/squid/squid-3.5.25/src/acl/IntRange.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/RegexData.cc -o /data/download/squid/squid-3.5.25/src/acl/RegexData.cc.ll
echo "132 /data/download/squid/squid-3.5.25/src/acl/RegexData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/StringData.cc -o /data/download/squid/squid-3.5.25/src/acl/StringData.cc.ll
echo "133 /data/download/squid/squid-3.5.25/src/acl/StringData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Time.cc -o /data/download/squid/squid-3.5.25/src/acl/Time.cc.ll
echo "134 /data/download/squid/squid-3.5.25/src/acl/Time.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/TimeData.cc -o /data/download/squid/squid-3.5.25/src/acl/TimeData.cc.ll
echo "135 /data/download/squid/squid-3.5.25/src/acl/TimeData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/AllOf.cc -o /data/download/squid/squid-3.5.25/src/acl/AllOf.cc.ll
echo "136 /data/download/squid/squid-3.5.25/src/acl/AllOf.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/AnyOf.cc -o /data/download/squid/squid-3.5.25/src/acl/AnyOf.cc.ll
echo "137 /data/download/squid/squid-3.5.25/src/acl/AnyOf.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Asn.cc -o /data/download/squid/squid-3.5.25/src/acl/Asn.cc.ll
echo "138 /data/download/squid/squid-3.5.25/src/acl/Asn.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Browser.cc -o /data/download/squid/squid-3.5.25/src/acl/Browser.cc.ll
echo "139 /data/download/squid/squid-3.5.25/src/acl/Browser.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/DestinationDomain.cc -o /data/download/squid/squid-3.5.25/src/acl/DestinationDomain.cc.ll
echo "140 /data/download/squid/squid-3.5.25/src/acl/DestinationDomain.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/DestinationIp.cc -o /data/download/squid/squid-3.5.25/src/acl/DestinationIp.cc.ll
echo "141 /data/download/squid/squid-3.5.25/src/acl/DestinationIp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/DomainData.cc -o /data/download/squid/squid-3.5.25/src/acl/DomainData.cc.ll
echo "142 /data/download/squid/squid-3.5.25/src/acl/DomainData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/ExtUser.cc -o /data/download/squid/squid-3.5.25/src/acl/ExtUser.cc.ll
echo "143 /data/download/squid/squid-3.5.25/src/acl/ExtUser.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/HierCodeData.cc -o /data/download/squid/squid-3.5.25/src/acl/HierCodeData.cc.ll
echo "144 /data/download/squid/squid-3.5.25/src/acl/HierCodeData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/HierCode.cc -o /data/download/squid/squid-3.5.25/src/acl/HierCode.cc.ll
echo "145 /data/download/squid/squid-3.5.25/src/acl/HierCode.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/HttpHeaderData.cc -o /data/download/squid/squid-3.5.25/src/acl/HttpHeaderData.cc.ll
echo "146 /data/download/squid/squid-3.5.25/src/acl/HttpHeaderData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/HttpRepHeader.cc -o /data/download/squid/squid-3.5.25/src/acl/HttpRepHeader.cc.ll
echo "147 /data/download/squid/squid-3.5.25/src/acl/HttpRepHeader.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/HttpReqHeader.cc -o /data/download/squid/squid-3.5.25/src/acl/HttpReqHeader.cc.ll
echo "148 /data/download/squid/squid-3.5.25/src/acl/HttpReqHeader.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/HttpStatus.cc -o /data/download/squid/squid-3.5.25/src/acl/HttpStatus.cc.ll
echo "149 /data/download/squid/squid-3.5.25/src/acl/HttpStatus.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Ip.cc -o /data/download/squid/squid-3.5.25/src/acl/Ip.cc.ll
echo "150 /data/download/squid/squid-3.5.25/src/acl/Ip.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/LocalIp.cc -o /data/download/squid/squid-3.5.25/src/acl/LocalIp.cc.ll
echo "151 /data/download/squid/squid-3.5.25/src/acl/LocalIp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/LocalPort.cc -o /data/download/squid/squid-3.5.25/src/acl/LocalPort.cc.ll
echo "152 /data/download/squid/squid-3.5.25/src/acl/LocalPort.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/MaxConnection.cc -o /data/download/squid/squid-3.5.25/src/acl/MaxConnection.cc.ll
echo "153 /data/download/squid/squid-3.5.25/src/acl/MaxConnection.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Method.cc -o /data/download/squid/squid-3.5.25/src/acl/Method.cc.ll
echo "154 /data/download/squid/squid-3.5.25/src/acl/Method.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/MethodData.cc -o /data/download/squid/squid-3.5.25/src/acl/MethodData.cc.ll
echo "155 /data/download/squid/squid-3.5.25/src/acl/MethodData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/MyPortName.cc -o /data/download/squid/squid-3.5.25/src/acl/MyPortName.cc.ll
echo "156 /data/download/squid/squid-3.5.25/src/acl/MyPortName.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Note.cc -o /data/download/squid/squid-3.5.25/src/acl/Note.cc.ll
echo "157 /data/download/squid/squid-3.5.25/src/acl/Note.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/NoteData.cc -o /data/download/squid/squid-3.5.25/src/acl/NoteData.cc.ll
echo "158 /data/download/squid/squid-3.5.25/src/acl/NoteData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/PeerName.cc -o /data/download/squid/squid-3.5.25/src/acl/PeerName.cc.ll
echo "159 /data/download/squid/squid-3.5.25/src/acl/PeerName.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Protocol.cc -o /data/download/squid/squid-3.5.25/src/acl/Protocol.cc.ll
echo "160 /data/download/squid/squid-3.5.25/src/acl/Protocol.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/ProtocolData.cc -o /data/download/squid/squid-3.5.25/src/acl/ProtocolData.cc.ll
echo "161 /data/download/squid/squid-3.5.25/src/acl/ProtocolData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Random.cc -o /data/download/squid/squid-3.5.25/src/acl/Random.cc.ll
echo "162 /data/download/squid/squid-3.5.25/src/acl/Random.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Referer.cc -o /data/download/squid/squid-3.5.25/src/acl/Referer.cc.ll
echo "163 /data/download/squid/squid-3.5.25/src/acl/Referer.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/ReplyMimeType.cc -o /data/download/squid/squid-3.5.25/src/acl/ReplyMimeType.cc.ll
echo "164 /data/download/squid/squid-3.5.25/src/acl/ReplyMimeType.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/RequestMimeType.cc -o /data/download/squid/squid-3.5.25/src/acl/RequestMimeType.cc.ll
echo "165 /data/download/squid/squid-3.5.25/src/acl/RequestMimeType.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/SourceDomain.cc -o /data/download/squid/squid-3.5.25/src/acl/SourceDomain.cc.ll
echo "166 /data/download/squid/squid-3.5.25/src/acl/SourceDomain.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/SourceIp.cc -o /data/download/squid/squid-3.5.25/src/acl/SourceIp.cc.ll
echo "167 /data/download/squid/squid-3.5.25/src/acl/SourceIp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Tag.cc -o /data/download/squid/squid-3.5.25/src/acl/Tag.cc.ll
echo "168 /data/download/squid/squid-3.5.25/src/acl/Tag.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Url.cc -o /data/download/squid/squid-3.5.25/src/acl/Url.cc.ll
echo "169 /data/download/squid/squid-3.5.25/src/acl/Url.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/UrlLogin.cc -o /data/download/squid/squid-3.5.25/src/acl/UrlLogin.cc.ll
echo "170 /data/download/squid/squid-3.5.25/src/acl/UrlLogin.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/UrlPath.cc -o /data/download/squid/squid-3.5.25/src/acl/UrlPath.cc.ll
echo "171 /data/download/squid/squid-3.5.25/src/acl/UrlPath.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/UrlPort.cc -o /data/download/squid/squid-3.5.25/src/acl/UrlPort.cc.ll
echo "172 /data/download/squid/squid-3.5.25/src/acl/UrlPort.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/UserData.cc -o /data/download/squid/squid-3.5.25/src/acl/UserData.cc.ll
echo "173 /data/download/squid/squid-3.5.25/src/acl/UserData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Gadgets.cc -o /data/download/squid/squid-3.5.25/src/acl/Gadgets.cc.ll
echo "174 /data/download/squid/squid-3.5.25/src/acl/Gadgets.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/AdaptationService.cc -o /data/download/squid/squid-3.5.25/src/acl/AdaptationService.cc.ll
echo "175 /data/download/squid/squid-3.5.25/src/acl/AdaptationService.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/AdaptationServiceData.cc -o /data/download/squid/squid-3.5.25/src/acl/AdaptationServiceData.cc.ll
echo "176 /data/download/squid/squid-3.5.25/src/acl/AdaptationServiceData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Arp.cc -o /data/download/squid/squid-3.5.25/src/acl/Arp.cc.ll
echo "177 /data/download/squid/squid-3.5.25/src/acl/Arp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/acl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/acl/Eui64.cc -o /data/download/squid/squid-3.5.25/src/acl/Eui64.cc.ll
echo "178 /data/download/squid/squid-3.5.25/src/acl/Eui64.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/format
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/format/Config.cc -o /data/download/squid/squid-3.5.25/src/format/Config.cc.ll
echo "179 /data/download/squid/squid-3.5.25/src/format/Config.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/format
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/format/Format.cc -o /data/download/squid/squid-3.5.25/src/format/Format.cc.ll
echo "180 /data/download/squid/squid-3.5.25/src/format/Format.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/format
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/format/Quoting.cc -o /data/download/squid/squid-3.5.25/src/format/Quoting.cc.ll
echo "181 /data/download/squid/squid-3.5.25/src/format/Quoting.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/format
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/format/Token.cc -o /data/download/squid/squid-3.5.25/src/format/Token.cc.ll
echo "182 /data/download/squid/squid-3.5.25/src/format/Token.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/clients
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/clients/Client.cc -o /data/download/squid/squid-3.5.25/src/clients/Client.cc.ll
echo "183 /data/download/squid/squid-3.5.25/src/clients/Client.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/clients
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/clients/FtpClient.cc -o /data/download/squid/squid-3.5.25/src/clients/FtpClient.cc.ll
echo "184 /data/download/squid/squid-3.5.25/src/clients/FtpClient.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/clients
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/clients/FtpGateway.cc -o /data/download/squid/squid-3.5.25/src/clients/FtpGateway.cc.ll
echo "185 /data/download/squid/squid-3.5.25/src/clients/FtpGateway.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/clients
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/clients/FtpRelay.cc -o /data/download/squid/squid-3.5.25/src/clients/FtpRelay.cc.ll
echo "186 /data/download/squid/squid-3.5.25/src/clients/FtpRelay.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/servers
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/servers/FtpServer.cc -o /data/download/squid/squid-3.5.25/src/servers/FtpServer.cc.ll
echo "187 /data/download/squid/squid-3.5.25/src/servers/FtpServer.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/servers
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/servers/HttpServer.cc -o /data/download/squid/squid-3.5.25/src/servers/HttpServer.cc.ll
echo "188 /data/download/squid/squid-3.5.25/src/servers/HttpServer.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/aufs/StoreFSaufs.cc -o /data/download/squid/squid-3.5.25/src/fs/aufs/StoreFSaufs.cc.ll
echo "189 /data/download/squid/squid-3.5.25/src/fs/aufs/StoreFSaufs.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/diskd/StoreFSdiskd.cc -o /data/download/squid/squid-3.5.25/src/fs/diskd/StoreFSdiskd.cc.ll
echo "190 /data/download/squid/squid-3.5.25/src/fs/diskd/StoreFSdiskd.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/rock/RockDbCell.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockDbCell.cc.ll
echo "191 /data/download/squid/squid-3.5.25/src/fs/rock/RockDbCell.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/rock/RockIoState.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockIoState.cc.ll
echo "192 /data/download/squid/squid-3.5.25/src/fs/rock/RockIoState.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/rock/RockIoRequests.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockIoRequests.cc.ll
echo "193 /data/download/squid/squid-3.5.25/src/fs/rock/RockIoRequests.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/rock/RockRebuild.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockRebuild.cc.ll
echo "194 /data/download/squid/squid-3.5.25/src/fs/rock/RockRebuild.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/rock/RockStoreFileSystem.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockStoreFileSystem.cc.ll
echo "195 /data/download/squid/squid-3.5.25/src/fs/rock/RockStoreFileSystem.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/rock/RockSwapDir.cc -o /data/download/squid/squid-3.5.25/src/fs/rock/RockSwapDir.cc.ll
echo "196 /data/download/squid/squid-3.5.25/src/fs/rock/RockSwapDir.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/ufs/StoreFSufs.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/StoreFSufs.cc.ll
echo "197 /data/download/squid/squid-3.5.25/src/fs/ufs/StoreFSufs.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStoreState.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStoreState.cc.ll
echo "198 /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStoreState.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapDir.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapDir.cc.ll
echo "199 /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapDir.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStrategy.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStrategy.cc.ll
echo "200 /data/download/squid/squid-3.5.25/src/fs/ufs/UFSStrategy.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/ufs/StoreSearchUFS.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/StoreSearchUFS.cc.ll
echo "201 /data/download/squid/squid-3.5.25/src/fs/ufs/StoreSearchUFS.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapLogParser.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapLogParser.cc.ll
echo "202 /data/download/squid/squid-3.5.25/src/fs/ufs/UFSSwapLogParser.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/ufs/RebuildState.cc -o /data/download/squid/squid-3.5.25/src/fs/ufs/RebuildState.cc.ll
echo "203 /data/download/squid/squid-3.5.25/src/fs/ufs/RebuildState.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/fs
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/fs/Module.cc -o /data/download/squid/squid-3.5.25/src/fs/Module.cc.ll
echo "204 /data/download/squid/squid-3.5.25/src/fs/Module.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/repl
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -I. -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/repl/lru/store_repl_lru.cc -o /data/download/squid/squid-3.5.25/src/repl/lru/store_repl_lru.cc.ll
echo "205 /data/download/squid/squid-3.5.25/src/repl/lru/store_repl_lru.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/basic
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/basic/Config.cc -o /data/download/squid/squid-3.5.25/src/auth/basic/Config.cc.ll
echo "206 /data/download/squid/squid-3.5.25/src/auth/basic/Config.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/basic
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/basic/Scheme.cc -o /data/download/squid/squid-3.5.25/src/auth/basic/Scheme.cc.ll
echo "207 /data/download/squid/squid-3.5.25/src/auth/basic/Scheme.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/basic
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/basic/User.cc -o /data/download/squid/squid-3.5.25/src/auth/basic/User.cc.ll
echo "208 /data/download/squid/squid-3.5.25/src/auth/basic/User.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/basic
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/basic/UserRequest.cc -o /data/download/squid/squid-3.5.25/src/auth/basic/UserRequest.cc.ll
echo "209 /data/download/squid/squid-3.5.25/src/auth/basic/UserRequest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/digest
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/digest/Config.cc -o /data/download/squid/squid-3.5.25/src/auth/digest/Config.cc.ll
echo "210 /data/download/squid/squid-3.5.25/src/auth/digest/Config.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/digest
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/digest/Scheme.cc -o /data/download/squid/squid-3.5.25/src/auth/digest/Scheme.cc.ll
echo "211 /data/download/squid/squid-3.5.25/src/auth/digest/Scheme.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/digest
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/digest/User.cc -o /data/download/squid/squid-3.5.25/src/auth/digest/User.cc.ll
echo "212 /data/download/squid/squid-3.5.25/src/auth/digest/User.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/digest
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/digest/UserRequest.cc -o /data/download/squid/squid-3.5.25/src/auth/digest/UserRequest.cc.ll
echo "213 /data/download/squid/squid-3.5.25/src/auth/digest/UserRequest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/negotiate
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/negotiate/Scheme.cc -o /data/download/squid/squid-3.5.25/src/auth/negotiate/Scheme.cc.ll
echo "214 /data/download/squid/squid-3.5.25/src/auth/negotiate/Scheme.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/negotiate
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/negotiate/Config.cc -o /data/download/squid/squid-3.5.25/src/auth/negotiate/Config.cc.ll
echo "215 /data/download/squid/squid-3.5.25/src/auth/negotiate/Config.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/negotiate
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/negotiate/User.cc -o /data/download/squid/squid-3.5.25/src/auth/negotiate/User.cc.ll
echo "216 /data/download/squid/squid-3.5.25/src/auth/negotiate/User.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/negotiate
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/negotiate/UserRequest.cc -o /data/download/squid/squid-3.5.25/src/auth/negotiate/UserRequest.cc.ll
echo "217 /data/download/squid/squid-3.5.25/src/auth/negotiate/UserRequest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/ntlm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/ntlm/Config.cc -o /data/download/squid/squid-3.5.25/src/auth/ntlm/Config.cc.ll
echo "218 /data/download/squid/squid-3.5.25/src/auth/ntlm/Config.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/ntlm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/ntlm/Scheme.cc -o /data/download/squid/squid-3.5.25/src/auth/ntlm/Scheme.cc.ll
echo "219 /data/download/squid/squid-3.5.25/src/auth/ntlm/Scheme.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/ntlm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/ntlm/User.cc -o /data/download/squid/squid-3.5.25/src/auth/ntlm/User.cc.ll
echo "220 /data/download/squid/squid-3.5.25/src/auth/ntlm/User.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth/ntlm
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/ntlm/UserRequest.cc -o /data/download/squid/squid-3.5.25/src/auth/ntlm/UserRequest.cc.ll
echo "221 /data/download/squid/squid-3.5.25/src/auth/ntlm/UserRequest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/Type.cc -o /data/download/squid/squid-3.5.25/src/auth/Type.cc.ll
echo "222 /data/download/squid/squid-3.5.25/src/auth/Type.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/Config.cc -o /data/download/squid/squid-3.5.25/src/auth/Config.cc.ll
echo "223 /data/download/squid/squid-3.5.25/src/auth/Config.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/CredentialState.cc -o /data/download/squid/squid-3.5.25/src/auth/CredentialState.cc.ll
echo "224 /data/download/squid/squid-3.5.25/src/auth/CredentialState.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/Gadgets.cc -o /data/download/squid/squid-3.5.25/src/auth/Gadgets.cc.ll
echo "225 /data/download/squid/squid-3.5.25/src/auth/Gadgets.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/Scheme.cc -o /data/download/squid/squid-3.5.25/src/auth/Scheme.cc.ll
echo "226 /data/download/squid/squid-3.5.25/src/auth/Scheme.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/State.cc -o /data/download/squid/squid-3.5.25/src/auth/State.cc.ll
echo "227 /data/download/squid/squid-3.5.25/src/auth/State.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/User.cc -o /data/download/squid/squid-3.5.25/src/auth/User.cc.ll
echo "228 /data/download/squid/squid-3.5.25/src/auth/User.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/UserRequest.cc -o /data/download/squid/squid-3.5.25/src/auth/UserRequest.cc.ll
echo "229 /data/download/squid/squid-3.5.25/src/auth/UserRequest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/Acl.cc -o /data/download/squid/squid-3.5.25/src/auth/Acl.cc.ll
echo "230 /data/download/squid/squid-3.5.25/src/auth/Acl.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/AclMaxUserIp.cc -o /data/download/squid/squid-3.5.25/src/auth/AclMaxUserIp.cc.ll
echo "231 /data/download/squid/squid-3.5.25/src/auth/AclMaxUserIp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/auth
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/auth/AclProxyAuth.cc -o /data/download/squid/squid-3.5.25/src/auth/AclProxyAuth.cc.ll
echo "232 /data/download/squid/squid-3.5.25/src/auth/AclProxyAuth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/http
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/http/MethodType.cc -o /data/download/squid/squid-3.5.25/src/http/MethodType.cc.ll
echo "233 /data/download/squid/squid-3.5.25/src/http/MethodType.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/http
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/http/StatusCode.cc -o /data/download/squid/squid-3.5.25/src/http/StatusCode.cc.ll
echo "234 /data/download/squid/squid-3.5.25/src/http/StatusCode.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/http
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/http/StatusLine.cc -o /data/download/squid/squid-3.5.25/src/http/StatusLine.cc.ll
echo "235 /data/download/squid/squid-3.5.25/src/http/StatusLine.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ip
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ip/Address.cc -o /data/download/squid/squid-3.5.25/src/ip/Address.cc.ll
echo "236 /data/download/squid/squid-3.5.25/src/ip/Address.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ip
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ip/Intercept.cc -o /data/download/squid/squid-3.5.25/src/ip/Intercept.cc.ll
echo "237 /data/download/squid/squid-3.5.25/src/ip/Intercept.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ip
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ip/QosConfig.cc -o /data/download/squid/squid-3.5.25/src/ip/QosConfig.cc.ll
echo "238 /data/download/squid/squid-3.5.25/src/ip/QosConfig.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ip
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ip/tools.cc -o /data/download/squid/squid-3.5.25/src/ip/tools.cc.ll
echo "239 /data/download/squid/squid-3.5.25/src/ip/tools.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/icmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=NULL -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/icmp/Icmp.cc -o /data/download/squid/squid-3.5.25/src/icmp/Icmp.cc.ll
echo "240 /data/download/squid/squid-3.5.25/src/icmp/Icmp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/icmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=NULL -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/icmp/IcmpSquid.cc -o /data/download/squid/squid-3.5.25/src/icmp/IcmpSquid.cc.ll
echo "241 /data/download/squid/squid-3.5.25/src/icmp/IcmpSquid.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/icmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=NULL -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/icmp/net_db.cc -o /data/download/squid/squid-3.5.25/src/icmp/net_db.cc.ll
echo "242 /data/download/squid/squid-3.5.25/src/icmp/net_db.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ident
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ident/AclIdent.cc -o /data/download/squid/squid-3.5.25/src/ident/AclIdent.cc.ll
echo "243 /data/download/squid/squid-3.5.25/src/ident/AclIdent.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ident
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ident/Ident.cc -o /data/download/squid/squid-3.5.25/src/ident/Ident.cc.ll
echo "244 /data/download/squid/squid-3.5.25/src/ident/Ident.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/access_log.cc -o /data/download/squid/squid-3.5.25/src/log/access_log.cc.ll
echo "245 /data/download/squid/squid-3.5.25/src/log/access_log.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/Config.cc -o /data/download/squid/squid-3.5.25/src/log/Config.cc.ll
echo "246 /data/download/squid/squid-3.5.25/src/log/Config.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/File.cc -o /data/download/squid/squid-3.5.25/src/log/File.cc.ll
echo "247 /data/download/squid/squid-3.5.25/src/log/File.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/FormatHttpdCombined.cc -o /data/download/squid/squid-3.5.25/src/log/FormatHttpdCombined.cc.ll
echo "248 /data/download/squid/squid-3.5.25/src/log/FormatHttpdCombined.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/FormatHttpdCommon.cc -o /data/download/squid/squid-3.5.25/src/log/FormatHttpdCommon.cc.ll
echo "249 /data/download/squid/squid-3.5.25/src/log/FormatHttpdCommon.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/FormatSquidCustom.cc -o /data/download/squid/squid-3.5.25/src/log/FormatSquidCustom.cc.ll
echo "250 /data/download/squid/squid-3.5.25/src/log/FormatSquidCustom.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/FormatSquidIcap.cc -o /data/download/squid/squid-3.5.25/src/log/FormatSquidIcap.cc.ll
echo "251 /data/download/squid/squid-3.5.25/src/log/FormatSquidIcap.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/FormatSquidNative.cc -o /data/download/squid/squid-3.5.25/src/log/FormatSquidNative.cc.ll
echo "252 /data/download/squid/squid-3.5.25/src/log/FormatSquidNative.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/FormatSquidReferer.cc -o /data/download/squid/squid-3.5.25/src/log/FormatSquidReferer.cc.ll
echo "253 /data/download/squid/squid-3.5.25/src/log/FormatSquidReferer.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/FormatSquidUseragent.cc -o /data/download/squid/squid-3.5.25/src/log/FormatSquidUseragent.cc.ll
echo "254 /data/download/squid/squid-3.5.25/src/log/FormatSquidUseragent.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/ModDaemon.cc -o /data/download/squid/squid-3.5.25/src/log/ModDaemon.cc.ll
echo "255 /data/download/squid/squid-3.5.25/src/log/ModDaemon.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/ModStdio.cc -o /data/download/squid/squid-3.5.25/src/log/ModStdio.cc.ll
echo "256 /data/download/squid/squid-3.5.25/src/log/ModStdio.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/ModSyslog.cc -o /data/download/squid/squid-3.5.25/src/log/ModSyslog.cc.ll
echo "257 /data/download/squid/squid-3.5.25/src/log/ModSyslog.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/ModUdp.cc -o /data/download/squid/squid-3.5.25/src/log/ModUdp.cc.ll
echo "258 /data/download/squid/squid-3.5.25/src/log/ModUdp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/CustomLog.cc -o /data/download/squid/squid-3.5.25/src/log/CustomLog.cc.ll
echo "259 /data/download/squid/squid-3.5.25/src/log/CustomLog.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/log
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/log/TcpLogger.cc -o /data/download/squid/squid-3.5.25/src/log/TcpLogger.cc.ll
echo "260 /data/download/squid/squid-3.5.25/src/log/TcpLogger.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/AtomicWord.cc -o /data/download/squid/squid-3.5.25/src/ipc/AtomicWord.cc.ll
echo "261 /data/download/squid/squid-3.5.25/src/ipc/AtomicWord.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/FdNotes.cc -o /data/download/squid/squid-3.5.25/src/ipc/FdNotes.cc.ll
echo "262 /data/download/squid/squid-3.5.25/src/ipc/FdNotes.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/Kid.cc -o /data/download/squid/squid-3.5.25/src/ipc/Kid.cc.ll
echo "263 /data/download/squid/squid-3.5.25/src/ipc/Kid.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/Kids.cc -o /data/download/squid/squid-3.5.25/src/ipc/Kids.cc.ll
echo "264 /data/download/squid/squid-3.5.25/src/ipc/Kids.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/MemMap.cc -o /data/download/squid/squid-3.5.25/src/ipc/MemMap.cc.ll
echo "265 /data/download/squid/squid-3.5.25/src/ipc/MemMap.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/Queue.cc -o /data/download/squid/squid-3.5.25/src/ipc/Queue.cc.ll
echo "266 /data/download/squid/squid-3.5.25/src/ipc/Queue.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/ReadWriteLock.cc -o /data/download/squid/squid-3.5.25/src/ipc/ReadWriteLock.cc.ll
echo "267 /data/download/squid/squid-3.5.25/src/ipc/ReadWriteLock.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/StartListening.cc -o /data/download/squid/squid-3.5.25/src/ipc/StartListening.cc.ll
echo "268 /data/download/squid/squid-3.5.25/src/ipc/StartListening.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/StoreMap.cc -o /data/download/squid/squid-3.5.25/src/ipc/StoreMap.cc.ll
echo "269 /data/download/squid/squid-3.5.25/src/ipc/StoreMap.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/StrandCoord.cc -o /data/download/squid/squid-3.5.25/src/ipc/StrandCoord.cc.ll
echo "270 /data/download/squid/squid-3.5.25/src/ipc/StrandCoord.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/StrandSearch.cc -o /data/download/squid/squid-3.5.25/src/ipc/StrandSearch.cc.ll
echo "271 /data/download/squid/squid-3.5.25/src/ipc/StrandSearch.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/SharedListen.cc -o /data/download/squid/squid-3.5.25/src/ipc/SharedListen.cc.ll
echo "272 /data/download/squid/squid-3.5.25/src/ipc/SharedListen.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/TypedMsgHdr.cc -o /data/download/squid/squid-3.5.25/src/ipc/TypedMsgHdr.cc.ll
echo "273 /data/download/squid/squid-3.5.25/src/ipc/TypedMsgHdr.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/Coordinator.cc -o /data/download/squid/squid-3.5.25/src/ipc/Coordinator.cc.ll
echo "274 /data/download/squid/squid-3.5.25/src/ipc/Coordinator.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/UdsOp.cc -o /data/download/squid/squid-3.5.25/src/ipc/UdsOp.cc.ll
echo "275 /data/download/squid/squid-3.5.25/src/ipc/UdsOp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/Port.cc -o /data/download/squid/squid-3.5.25/src/ipc/Port.cc.ll
echo "276 /data/download/squid/squid-3.5.25/src/ipc/Port.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/Strand.cc -o /data/download/squid/squid-3.5.25/src/ipc/Strand.cc.ll
echo "277 /data/download/squid/squid-3.5.25/src/ipc/Strand.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/Forwarder.cc -o /data/download/squid/squid-3.5.25/src/ipc/Forwarder.cc.ll
echo "278 /data/download/squid/squid-3.5.25/src/ipc/Forwarder.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/Inquirer.cc -o /data/download/squid/squid-3.5.25/src/ipc/Inquirer.cc.ll
echo "279 /data/download/squid/squid-3.5.25/src/ipc/Inquirer.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/mem/Page.cc -o /data/download/squid/squid-3.5.25/src/ipc/mem/Page.cc.ll
echo "280 /data/download/squid/squid-3.5.25/src/ipc/mem/Page.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/mem/PagePool.cc -o /data/download/squid/squid-3.5.25/src/ipc/mem/PagePool.cc.ll
echo "281 /data/download/squid/squid-3.5.25/src/ipc/mem/PagePool.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/mem/Pages.cc -o /data/download/squid/squid-3.5.25/src/ipc/mem/Pages.cc.ll
echo "282 /data/download/squid/squid-3.5.25/src/ipc/mem/Pages.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/mem/PageStack.cc -o /data/download/squid/squid-3.5.25/src/ipc/mem/PageStack.cc.ll
echo "283 /data/download/squid/squid-3.5.25/src/ipc/mem/PageStack.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/ipc
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_STATEDIR=\"/usr/local/squid/var/run/squid\" -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/ipc/mem/Segment.cc -o /data/download/squid/squid-3.5.25/src/ipc/mem/Segment.cc.ll
echo "284 /data/download/squid/squid-3.5.25/src/ipc/mem/Segment.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/Action.cc -o /data/download/squid/squid-3.5.25/src/mgr/Action.cc.ll
echo "285 /data/download/squid/squid-3.5.25/src/mgr/Action.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/ActionParams.cc -o /data/download/squid/squid-3.5.25/src/mgr/ActionParams.cc.ll
echo "286 /data/download/squid/squid-3.5.25/src/mgr/ActionParams.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/ActionPasswordList.cc -o /data/download/squid/squid-3.5.25/src/mgr/ActionPasswordList.cc.ll
echo "287 /data/download/squid/squid-3.5.25/src/mgr/ActionPasswordList.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/ActionWriter.cc -o /data/download/squid/squid-3.5.25/src/mgr/ActionWriter.cc.ll
echo "288 /data/download/squid/squid-3.5.25/src/mgr/ActionWriter.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/BasicActions.cc -o /data/download/squid/squid-3.5.25/src/mgr/BasicActions.cc.ll
echo "289 /data/download/squid/squid-3.5.25/src/mgr/BasicActions.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/Command.cc -o /data/download/squid/squid-3.5.25/src/mgr/Command.cc.ll
echo "290 /data/download/squid/squid-3.5.25/src/mgr/Command.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/CountersAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/CountersAction.cc.ll
echo "291 /data/download/squid/squid-3.5.25/src/mgr/CountersAction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/Filler.cc -o /data/download/squid/squid-3.5.25/src/mgr/Filler.cc.ll
echo "292 /data/download/squid/squid-3.5.25/src/mgr/Filler.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/Forwarder.cc -o /data/download/squid/squid-3.5.25/src/mgr/Forwarder.cc.ll
echo "293 /data/download/squid/squid-3.5.25/src/mgr/Forwarder.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/FunAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/FunAction.cc.ll
echo "294 /data/download/squid/squid-3.5.25/src/mgr/FunAction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/InfoAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/InfoAction.cc.ll
echo "295 /data/download/squid/squid-3.5.25/src/mgr/InfoAction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/Inquirer.cc -o /data/download/squid/squid-3.5.25/src/mgr/Inquirer.cc.ll
echo "296 /data/download/squid/squid-3.5.25/src/mgr/Inquirer.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/IntervalAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/IntervalAction.cc.ll
echo "297 /data/download/squid/squid-3.5.25/src/mgr/IntervalAction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/IoAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/IoAction.cc.ll
echo "298 /data/download/squid/squid-3.5.25/src/mgr/IoAction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/Registration.cc -o /data/download/squid/squid-3.5.25/src/mgr/Registration.cc.ll
echo "299 /data/download/squid/squid-3.5.25/src/mgr/Registration.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/Request.cc -o /data/download/squid/squid-3.5.25/src/mgr/Request.cc.ll
echo "300 /data/download/squid/squid-3.5.25/src/mgr/Request.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/Response.cc -o /data/download/squid/squid-3.5.25/src/mgr/Response.cc.ll
echo "301 /data/download/squid/squid-3.5.25/src/mgr/Response.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/ServiceTimesAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/ServiceTimesAction.cc.ll
echo "302 /data/download/squid/squid-3.5.25/src/mgr/ServiceTimesAction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/StoreIoAction.cc -o /data/download/squid/squid-3.5.25/src/mgr/StoreIoAction.cc.ll
echo "303 /data/download/squid/squid-3.5.25/src/mgr/StoreIoAction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/StoreToCommWriter.cc -o /data/download/squid/squid-3.5.25/src/mgr/StoreToCommWriter.cc.ll
echo "304 /data/download/squid/squid-3.5.25/src/mgr/StoreToCommWriter.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/QueryParams.cc -o /data/download/squid/squid-3.5.25/src/mgr/QueryParams.cc.ll
echo "305 /data/download/squid/squid-3.5.25/src/mgr/QueryParams.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/IntParam.cc -o /data/download/squid/squid-3.5.25/src/mgr/IntParam.cc.ll
echo "306 /data/download/squid/squid-3.5.25/src/mgr/IntParam.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/mgr
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/mgr/StringParam.cc -o /data/download/squid/squid-3.5.25/src/mgr/StringParam.cc.ll
echo "307 /data/download/squid/squid-3.5.25/src/mgr/StringParam.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/snmp/Forwarder.cc -o /data/download/squid/squid-3.5.25/src/snmp/Forwarder.cc.ll
echo "308 /data/download/squid/squid-3.5.25/src/snmp/Forwarder.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/snmp/Inquirer.cc -o /data/download/squid/squid-3.5.25/src/snmp/Inquirer.cc.ll
echo "309 /data/download/squid/squid-3.5.25/src/snmp/Inquirer.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/snmp/Pdu.cc -o /data/download/squid/squid-3.5.25/src/snmp/Pdu.cc.ll
echo "310 /data/download/squid/squid-3.5.25/src/snmp/Pdu.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/snmp/Request.cc -o /data/download/squid/squid-3.5.25/src/snmp/Request.cc.ll
echo "311 /data/download/squid/squid-3.5.25/src/snmp/Request.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/snmp/Response.cc -o /data/download/squid/squid-3.5.25/src/snmp/Response.cc.ll
echo "312 /data/download/squid/squid-3.5.25/src/snmp/Response.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/snmp/Session.cc -o /data/download/squid/squid-3.5.25/src/snmp/Session.cc.ll
echo "313 /data/download/squid/squid-3.5.25/src/snmp/Session.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/snmp
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/snmp/Var.cc -o /data/download/squid/squid-3.5.25/src/snmp/Var.cc.ll
echo "314 /data/download/squid/squid-3.5.25/src/snmp/Var.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/Client.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Client.cc.ll
echo "315 /data/download/squid/squid-3.5.25/src/adaptation/icap/Client.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/Config.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Config.cc.ll
echo "316 /data/download/squid/squid-3.5.25/src/adaptation/icap/Config.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/Elements.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Elements.cc.ll
echo "317 /data/download/squid/squid-3.5.25/src/adaptation/icap/Elements.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/Options.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Options.cc.ll
echo "318 /data/download/squid/squid-3.5.25/src/adaptation/icap/Options.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/ServiceRep.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/ServiceRep.cc.ll
echo "319 /data/download/squid/squid-3.5.25/src/adaptation/icap/ServiceRep.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/Launcher.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Launcher.cc.ll
echo "320 /data/download/squid/squid-3.5.25/src/adaptation/icap/Launcher.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/OptXact.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/OptXact.cc.ll
echo "321 /data/download/squid/squid-3.5.25/src/adaptation/icap/OptXact.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/Xaction.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/Xaction.cc.ll
echo "322 /data/download/squid/squid-3.5.25/src/adaptation/icap/Xaction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/ModXact.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/ModXact.cc.ll
echo "323 /data/download/squid/squid-3.5.25/src/adaptation/icap/ModXact.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/icap_log.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/icap_log.cc.ll
echo "324 /data/download/squid/squid-3.5.25/src/adaptation/icap/icap_log.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation/icap
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../../.. -I../../../include -I../../../lib -I../../../src -I../../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/icap/History.cc -o /data/download/squid/squid-3.5.25/src/adaptation/icap/History.cc.ll
echo "325 /data/download/squid/squid-3.5.25/src/adaptation/icap/History.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/AccessCheck.cc -o /data/download/squid/squid-3.5.25/src/adaptation/AccessCheck.cc.ll
echo "326 /data/download/squid/squid-3.5.25/src/adaptation/AccessCheck.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/AccessRule.cc -o /data/download/squid/squid-3.5.25/src/adaptation/AccessRule.cc.ll
echo "327 /data/download/squid/squid-3.5.25/src/adaptation/AccessRule.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/Answer.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Answer.cc.ll
echo "328 /data/download/squid/squid-3.5.25/src/adaptation/Answer.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/Config.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Config.cc.ll
echo "329 /data/download/squid/squid-3.5.25/src/adaptation/Config.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/DynamicGroupCfg.cc -o /data/download/squid/squid-3.5.25/src/adaptation/DynamicGroupCfg.cc.ll
echo "330 /data/download/squid/squid-3.5.25/src/adaptation/DynamicGroupCfg.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/Elements.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Elements.cc.ll
echo "331 /data/download/squid/squid-3.5.25/src/adaptation/Elements.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/Initiate.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Initiate.cc.ll
echo "332 /data/download/squid/squid-3.5.25/src/adaptation/Initiate.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/Initiator.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Initiator.cc.ll
echo "333 /data/download/squid/squid-3.5.25/src/adaptation/Initiator.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/Iterator.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Iterator.cc.ll
echo "334 /data/download/squid/squid-3.5.25/src/adaptation/Iterator.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/Message.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Message.cc.ll
echo "335 /data/download/squid/squid-3.5.25/src/adaptation/Message.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/Service.cc -o /data/download/squid/squid-3.5.25/src/adaptation/Service.cc.ll
echo "336 /data/download/squid/squid-3.5.25/src/adaptation/Service.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/ServiceConfig.cc -o /data/download/squid/squid-3.5.25/src/adaptation/ServiceConfig.cc.ll
echo "337 /data/download/squid/squid-3.5.25/src/adaptation/ServiceConfig.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/ServiceGroups.cc -o /data/download/squid/squid-3.5.25/src/adaptation/ServiceGroups.cc.ll
echo "338 /data/download/squid/squid-3.5.25/src/adaptation/ServiceGroups.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/ServiceFilter.cc -o /data/download/squid/squid-3.5.25/src/adaptation/ServiceFilter.cc.ll
echo "339 /data/download/squid/squid-3.5.25/src/adaptation/ServiceFilter.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/adaptation
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/adaptation/History.cc -o /data/download/squid/squid-3.5.25/src/adaptation/History.cc.ll
echo "340 /data/download/squid/squid-3.5.25/src/adaptation/History.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskFile.cc.ll
echo "341 /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskFile.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOStrategy.cc.ll
echo "342 /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOStrategy.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOModule.cc.ll
echo "343 /data/download/squid/squid-3.5.25/src/DiskIO/AIO/AIODiskIOModule.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingFile.cc.ll
echo "344 /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingFile.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingIOStrategy.cc.ll
echo "345 /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingIOStrategy.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingDiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingDiskIOModule.cc.ll
echo "346 /data/download/squid/squid-3.5.25/src/DiskIO/Blocking/BlockingDiskIOModule.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdFile.cc.ll
echo "347 /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdFile.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdIOStrategy.cc.ll
echo "348 /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdIOStrategy.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskDaemonDiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskDaemonDiskIOModule.cc.ll
echo "349 /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskDaemonDiskIOModule.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdAction.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdAction.cc.ll
echo "350 /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/DiskdAction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/aiops.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/aiops.cc.ll
echo "351 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/aiops.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/CommIO.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/CommIO.cc.ll
echo "352 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/CommIO.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/async_io.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/async_io.cc.ll
echo "353 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/async_io.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskFile.cc.ll
echo "354 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskFile.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskIOModule.cc.ll
echo "355 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsDiskIOModule.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsIOStrategy.cc.ll
echo "356 /data/download/squid/squid-3.5.25/src/DiskIO/DiskThreads/DiskThreadsIOStrategy.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoFile.cc.ll
echo "357 /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoFile.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoIOStrategy.cc.ll
echo "358 /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoIOStrategy.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoDiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoDiskIOModule.cc.ll
echo "359 /data/download/squid/squid-3.5.25/src/DiskIO/IpcIo/IpcIoDiskIOModule.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedFile.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedFile.cc.ll
echo "360 /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedFile.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedIOStrategy.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedIOStrategy.cc.ll
echo "361 /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedIOStrategy.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedDiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedDiskIOModule.cc.ll
echo "362 /data/download/squid/squid-3.5.25/src/DiskIO/Mmapped/MmappedDiskIOModule.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/comm.cc -o /data/download/squid/squid-3.5.25/src/comm.cc.ll
echo "363 /data/download/squid/squid-3.5.25/src/comm.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/CommCalls.cc -o /data/download/squid/squid-3.5.25/src/CommCalls.cc.ll
echo "364 /data/download/squid/squid-3.5.25/src/CommCalls.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/DescriptorSet.cc -o /data/download/squid/squid-3.5.25/src/DescriptorSet.cc.ll
echo "365 /data/download/squid/squid-3.5.25/src/DescriptorSet.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -DPIC -S /data/download/squid/squid-3.5.25/src/SquidConfig.cc -o /data/download/squid/squid-3.5.25/src/SquidConfig.cc.ll
echo "366 /data/download/squid/squid-3.5.25/src/SquidConfig.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/diskd.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/diskd.cc.ll
echo "367 /data/download/squid/squid-3.5.25/src/DiskIO/DiskDaemon/diskd.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/time.cc -o /data/download/squid/squid-3.5.25/src/time.cc.ll
echo "368 /data/download/squid/squid-3.5.25/src/time.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/unlinkd_daemon.cc -o /data/download/squid/squid-3.5.25/src/unlinkd_daemon.cc.ll
echo "369 /data/download/squid/squid-3.5.25/src/unlinkd_daemon.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/AclRegs.cc -o /data/download/squid/squid-3.5.25/src/AclRegs.cc.ll
echo "370 /data/download/squid/squid-3.5.25/src/AclRegs.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/AuthReg.cc -o /data/download/squid/squid-3.5.25/src/AuthReg.cc.ll
echo "371 /data/download/squid/squid-3.5.25/src/AuthReg.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/AccessLogEntry.cc -o /data/download/squid/squid-3.5.25/src/AccessLogEntry.cc.ll
echo "372 /data/download/squid/squid-3.5.25/src/AccessLogEntry.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/AsyncEngine.cc -o /data/download/squid/squid-3.5.25/src/AsyncEngine.cc.ll
echo "373 /data/download/squid/squid-3.5.25/src/AsyncEngine.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/YesNoNone.cc -o /data/download/squid/squid-3.5.25/src/YesNoNone.cc.ll
echo "374 /data/download/squid/squid-3.5.25/src/YesNoNone.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/cache_cf.cc -o /data/download/squid/squid-3.5.25/src/cache_cf.cc.ll
echo "375 /data/download/squid/squid-3.5.25/src/cache_cf.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/CacheDigest.cc -o /data/download/squid/squid-3.5.25/src/CacheDigest.cc.ll
echo "376 /data/download/squid/squid-3.5.25/src/CacheDigest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/cache_manager.cc -o /data/download/squid/squid-3.5.25/src/cache_manager.cc.ll
echo "377 /data/download/squid/squid-3.5.25/src/cache_manager.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/carp.cc -o /data/download/squid/squid-3.5.25/src/carp.cc.ll
echo "378 /data/download/squid/squid-3.5.25/src/carp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/cbdata.cc -o /data/download/squid/squid-3.5.25/src/cbdata.cc.ll
echo "379 /data/download/squid/squid-3.5.25/src/cbdata.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/ChunkedCodingParser.cc -o /data/download/squid/squid-3.5.25/src/ChunkedCodingParser.cc.ll
echo "380 /data/download/squid/squid-3.5.25/src/ChunkedCodingParser.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/client_db.cc -o /data/download/squid/squid-3.5.25/src/client_db.cc.ll
echo "381 /data/download/squid/squid-3.5.25/src/client_db.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/client_side.cc -o /data/download/squid/squid-3.5.25/src/client_side.cc.ll
echo "382 /data/download/squid/squid-3.5.25/src/client_side.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/client_side_reply.cc -o /data/download/squid/squid-3.5.25/src/client_side_reply.cc.ll
echo "383 /data/download/squid/squid-3.5.25/src/client_side_reply.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/client_side_request.cc -o /data/download/squid/squid-3.5.25/src/client_side_request.cc.ll
echo "384 /data/download/squid/squid-3.5.25/src/client_side_request.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/BodyPipe.cc -o /data/download/squid/squid-3.5.25/src/BodyPipe.cc.ll
echo "385 /data/download/squid/squid-3.5.25/src/BodyPipe.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/clientStream.cc -o /data/download/squid/squid-3.5.25/src/clientStream.cc.ll
echo "386 /data/download/squid/squid-3.5.25/src/clientStream.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/CollapsedForwarding.cc -o /data/download/squid/squid-3.5.25/src/CollapsedForwarding.cc.ll
echo "387 /data/download/squid/squid-3.5.25/src/CollapsedForwarding.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/CompletionDispatcher.cc -o /data/download/squid/squid-3.5.25/src/CompletionDispatcher.cc.ll
echo "388 /data/download/squid/squid-3.5.25/src/CompletionDispatcher.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/ConfigOption.cc -o /data/download/squid/squid-3.5.25/src/ConfigOption.cc.ll
echo "389 /data/download/squid/squid-3.5.25/src/ConfigOption.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/ConfigParser.cc -o /data/download/squid/squid-3.5.25/src/ConfigParser.cc.ll
echo "390 /data/download/squid/squid-3.5.25/src/ConfigParser.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/CpuAffinity.cc -o /data/download/squid/squid-3.5.25/src/CpuAffinity.cc.ll
echo "391 /data/download/squid/squid-3.5.25/src/CpuAffinity.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/CpuAffinityMap.cc -o /data/download/squid/squid-3.5.25/src/CpuAffinityMap.cc.ll
echo "392 /data/download/squid/squid-3.5.25/src/CpuAffinityMap.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/CpuAffinitySet.cc -o /data/download/squid/squid-3.5.25/src/CpuAffinitySet.cc.ll
echo "393 /data/download/squid/squid-3.5.25/src/CpuAffinitySet.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/debug.cc -o /data/download/squid/squid-3.5.25/src/debug.cc.ll
echo "394 /data/download/squid/squid-3.5.25/src/debug.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/disk.cc -o /data/download/squid/squid-3.5.25/src/disk.cc.ll
echo "395 /data/download/squid/squid-3.5.25/src/disk.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModule.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModule.cc.ll
echo "396 /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModule.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/ReadRequest.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/ReadRequest.cc.ll
echo "397 /data/download/squid/squid-3.5.25/src/DiskIO/ReadRequest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/WriteRequest.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/WriteRequest.cc.ll
echo "398 /data/download/squid/squid-3.5.25/src/DiskIO/WriteRequest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/dlink.cc -o /data/download/squid/squid-3.5.25/src/dlink.cc.ll
echo "399 /data/download/squid/squid-3.5.25/src/dlink.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/dns_internal.cc -o /data/download/squid/squid-3.5.25/src/dns_internal.cc.ll
echo "400 /data/download/squid/squid-3.5.25/src/dns_internal.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DnsLookupDetails.cc -o /data/download/squid/squid-3.5.25/src/DnsLookupDetails.cc.ll
echo "401 /data/download/squid/squid-3.5.25/src/DnsLookupDetails.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/errorpage.cc -o /data/download/squid/squid-3.5.25/src/errorpage.cc.ll
echo "402 /data/download/squid/squid-3.5.25/src/errorpage.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/ETag.cc -o /data/download/squid/squid-3.5.25/src/ETag.cc.ll
echo "403 /data/download/squid/squid-3.5.25/src/ETag.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/event.cc -o /data/download/squid/squid-3.5.25/src/event.cc.ll
echo "404 /data/download/squid/squid-3.5.25/src/event.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/EventLoop.cc -o /data/download/squid/squid-3.5.25/src/EventLoop.cc.ll
echo "405 /data/download/squid/squid-3.5.25/src/EventLoop.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/external_acl.cc -o /data/download/squid/squid-3.5.25/src/external_acl.cc.ll
echo "406 /data/download/squid/squid-3.5.25/src/external_acl.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/ExternalACLEntry.cc -o /data/download/squid/squid-3.5.25/src/ExternalACLEntry.cc.ll
echo "407 /data/download/squid/squid-3.5.25/src/ExternalACLEntry.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/FadingCounter.cc -o /data/download/squid/squid-3.5.25/src/FadingCounter.cc.ll
echo "408 /data/download/squid/squid-3.5.25/src/FadingCounter.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/fatal.cc -o /data/download/squid/squid-3.5.25/src/fatal.cc.ll
echo "409 /data/download/squid/squid-3.5.25/src/fatal.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/fd.cc -o /data/download/squid/squid-3.5.25/src/fd.cc.ll
echo "410 /data/download/squid/squid-3.5.25/src/fd.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/fde.cc -o /data/download/squid/squid-3.5.25/src/fde.cc.ll
echo "411 /data/download/squid/squid-3.5.25/src/fde.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/filemap.cc -o /data/download/squid/squid-3.5.25/src/filemap.cc.ll
echo "412 /data/download/squid/squid-3.5.25/src/filemap.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/fqdncache.cc -o /data/download/squid/squid-3.5.25/src/fqdncache.cc.ll
echo "413 /data/download/squid/squid-3.5.25/src/fqdncache.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/FwdState.cc -o /data/download/squid/squid-3.5.25/src/FwdState.cc.ll
echo "414 /data/download/squid/squid-3.5.25/src/FwdState.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/gopher.cc -o /data/download/squid/squid-3.5.25/src/gopher.cc.ll
echo "415 /data/download/squid/squid-3.5.25/src/gopher.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/helper.cc -o /data/download/squid/squid-3.5.25/src/helper.cc.ll
echo "416 /data/download/squid/squid-3.5.25/src/helper.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/htcp.cc -o /data/download/squid/squid-3.5.25/src/htcp.cc.ll
echo "417 /data/download/squid/squid-3.5.25/src/htcp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/http.cc -o /data/download/squid/squid-3.5.25/src/http.cc.ll
echo "418 /data/download/squid/squid-3.5.25/src/http.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpHdrCc.cc -o /data/download/squid/squid-3.5.25/src/HttpHdrCc.cc.ll
echo "419 /data/download/squid/squid-3.5.25/src/HttpHdrCc.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpHdrRange.cc -o /data/download/squid/squid-3.5.25/src/HttpHdrRange.cc.ll
echo "420 /data/download/squid/squid-3.5.25/src/HttpHdrRange.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpHdrSc.cc -o /data/download/squid/squid-3.5.25/src/HttpHdrSc.cc.ll
echo "421 /data/download/squid/squid-3.5.25/src/HttpHdrSc.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpHdrScTarget.cc -o /data/download/squid/squid-3.5.25/src/HttpHdrScTarget.cc.ll
echo "422 /data/download/squid/squid-3.5.25/src/HttpHdrScTarget.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpHdrContRange.cc -o /data/download/squid/squid-3.5.25/src/HttpHdrContRange.cc.ll
echo "423 /data/download/squid/squid-3.5.25/src/HttpHdrContRange.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpHeader.cc -o /data/download/squid/squid-3.5.25/src/HttpHeader.cc.ll
echo "424 /data/download/squid/squid-3.5.25/src/HttpHeader.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpHeaderTools.cc -o /data/download/squid/squid-3.5.25/src/HttpHeaderTools.cc.ll
echo "425 /data/download/squid/squid-3.5.25/src/HttpHeaderTools.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpBody.cc -o /data/download/squid/squid-3.5.25/src/HttpBody.cc.ll
echo "426 /data/download/squid/squid-3.5.25/src/HttpBody.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpMsg.cc -o /data/download/squid/squid-3.5.25/src/HttpMsg.cc.ll
echo "427 /data/download/squid/squid-3.5.25/src/HttpMsg.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpParser.cc -o /data/download/squid/squid-3.5.25/src/HttpParser.cc.ll
echo "428 /data/download/squid/squid-3.5.25/src/HttpParser.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpReply.cc -o /data/download/squid/squid-3.5.25/src/HttpReply.cc.ll
echo "429 /data/download/squid/squid-3.5.25/src/HttpReply.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/RequestFlags.cc -o /data/download/squid/squid-3.5.25/src/RequestFlags.cc.ll
echo "430 /data/download/squid/squid-3.5.25/src/RequestFlags.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpRequest.cc -o /data/download/squid/squid-3.5.25/src/HttpRequest.cc.ll
echo "431 /data/download/squid/squid-3.5.25/src/HttpRequest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/HttpRequestMethod.cc -o /data/download/squid/squid-3.5.25/src/HttpRequestMethod.cc.ll
echo "432 /data/download/squid/squid-3.5.25/src/HttpRequestMethod.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/icp_v2.cc -o /data/download/squid/squid-3.5.25/src/icp_v2.cc.ll
echo "433 /data/download/squid/squid-3.5.25/src/icp_v2.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/icp_v3.cc -o /data/download/squid/squid-3.5.25/src/icp_v3.cc.ll
echo "434 /data/download/squid/squid-3.5.25/src/icp_v3.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/int.cc -o /data/download/squid/squid-3.5.25/src/int.cc.ll
echo "435 /data/download/squid/squid-3.5.25/src/int.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/internal.cc -o /data/download/squid/squid-3.5.25/src/internal.cc.ll
echo "436 /data/download/squid/squid-3.5.25/src/internal.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/ipc.cc -o /data/download/squid/squid-3.5.25/src/ipc.cc.ll
echo "437 /data/download/squid/squid-3.5.25/src/ipc.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/ipcache.cc -o /data/download/squid/squid-3.5.25/src/ipcache.cc.ll
echo "438 /data/download/squid/squid-3.5.25/src/ipcache.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/SquidList.cc -o /data/download/squid/squid-3.5.25/src/SquidList.cc.ll
echo "439 /data/download/squid/squid-3.5.25/src/SquidList.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/main.cc -o /data/download/squid/squid-3.5.25/src/main.cc.ll
echo "440 /data/download/squid/squid-3.5.25/src/main.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/MasterXaction.cc -o /data/download/squid/squid-3.5.25/src/MasterXaction.cc.ll
echo "441 /data/download/squid/squid-3.5.25/src/MasterXaction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/mem.cc -o /data/download/squid/squid-3.5.25/src/mem.cc.ll
echo "442 /data/download/squid/squid-3.5.25/src/mem.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/mem_node.cc -o /data/download/squid/squid-3.5.25/src/mem_node.cc.ll
echo "443 /data/download/squid/squid-3.5.25/src/mem_node.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/MemBuf.cc -o /data/download/squid/squid-3.5.25/src/MemBuf.cc.ll
echo "444 /data/download/squid/squid-3.5.25/src/MemBuf.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/MemObject.cc -o /data/download/squid/squid-3.5.25/src/MemObject.cc.ll
echo "445 /data/download/squid/squid-3.5.25/src/MemObject.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/mime.cc -o /data/download/squid/squid-3.5.25/src/mime.cc.ll
echo "446 /data/download/squid/squid-3.5.25/src/mime.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/mime_header.cc -o /data/download/squid/squid-3.5.25/src/mime_header.cc.ll
echo "447 /data/download/squid/squid-3.5.25/src/mime_header.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/multicast.cc -o /data/download/squid/squid-3.5.25/src/multicast.cc.ll
echo "448 /data/download/squid/squid-3.5.25/src/multicast.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/neighbors.cc -o /data/download/squid/squid-3.5.25/src/neighbors.cc.ll
echo "449 /data/download/squid/squid-3.5.25/src/neighbors.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/Notes.cc -o /data/download/squid/squid-3.5.25/src/Notes.cc.ll
echo "450 /data/download/squid/squid-3.5.25/src/Notes.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/Packer.cc -o /data/download/squid/squid-3.5.25/src/Packer.cc.ll
echo "451 /data/download/squid/squid-3.5.25/src/Packer.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/Parsing.cc -o /data/download/squid/squid-3.5.25/src/Parsing.cc.ll
echo "452 /data/download/squid/squid-3.5.25/src/Parsing.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/pconn.cc -o /data/download/squid/squid-3.5.25/src/pconn.cc.ll
echo "453 /data/download/squid/squid-3.5.25/src/pconn.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/peer_digest.cc -o /data/download/squid/squid-3.5.25/src/peer_digest.cc.ll
echo "454 /data/download/squid/squid-3.5.25/src/peer_digest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/peer_proxy_negotiate_auth.cc -o /data/download/squid/squid-3.5.25/src/peer_proxy_negotiate_auth.cc.ll
echo "455 /data/download/squid/squid-3.5.25/src/peer_proxy_negotiate_auth.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/peer_select.cc -o /data/download/squid/squid-3.5.25/src/peer_select.cc.ll
echo "456 /data/download/squid/squid-3.5.25/src/peer_select.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/peer_sourcehash.cc -o /data/download/squid/squid-3.5.25/src/peer_sourcehash.cc.ll
echo "457 /data/download/squid/squid-3.5.25/src/peer_sourcehash.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/peer_userhash.cc -o /data/download/squid/squid-3.5.25/src/peer_userhash.cc.ll
echo "458 /data/download/squid/squid-3.5.25/src/peer_userhash.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/PeerPoolMgr.cc -o /data/download/squid/squid-3.5.25/src/PeerPoolMgr.cc.ll
echo "459 /data/download/squid/squid-3.5.25/src/PeerPoolMgr.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/redirect.cc -o /data/download/squid/squid-3.5.25/src/redirect.cc.ll
echo "460 /data/download/squid/squid-3.5.25/src/redirect.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/refresh.cc -o /data/download/squid/squid-3.5.25/src/refresh.cc.ll
echo "461 /data/download/squid/squid-3.5.25/src/refresh.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/RemovalPolicy.cc -o /data/download/squid/squid-3.5.25/src/RemovalPolicy.cc.ll
echo "462 /data/download/squid/squid-3.5.25/src/RemovalPolicy.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/send-announce.cc -o /data/download/squid/squid-3.5.25/src/send-announce.cc.ll
echo "463 /data/download/squid/squid-3.5.25/src/send-announce.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/MemBlob.cc -o /data/download/squid/squid-3.5.25/src/MemBlob.cc.ll
echo "464 /data/download/squid/squid-3.5.25/src/MemBlob.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/SBuf.cc -o /data/download/squid/squid-3.5.25/src/SBuf.cc.ll
echo "465 /data/download/squid/squid-3.5.25/src/SBuf.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/SBufExceptions.cc -o /data/download/squid/squid-3.5.25/src/SBufExceptions.cc.ll
echo "466 /data/download/squid/squid-3.5.25/src/SBufExceptions.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/SBufDetailedStats.cc -o /data/download/squid/squid-3.5.25/src/SBufDetailedStats.cc.ll
echo "467 /data/download/squid/squid-3.5.25/src/SBufDetailedStats.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/SBufStatsAction.cc -o /data/download/squid/squid-3.5.25/src/SBufStatsAction.cc.ll
echo "468 /data/download/squid/squid-3.5.25/src/SBufStatsAction.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/snmp_core.cc -o /data/download/squid/squid-3.5.25/src/snmp_core.cc.ll
echo "469 /data/download/squid/squid-3.5.25/src/snmp_core.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/snmp_agent.cc -o /data/download/squid/squid-3.5.25/src/snmp_agent.cc.ll
echo "470 /data/download/squid/squid-3.5.25/src/snmp_agent.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/SquidMath.cc -o /data/download/squid/squid-3.5.25/src/SquidMath.cc.ll
echo "471 /data/download/squid/squid-3.5.25/src/SquidMath.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/SquidNew.cc -o /data/download/squid/squid-3.5.25/src/SquidNew.cc.ll
echo "472 /data/download/squid/squid-3.5.25/src/SquidNew.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/stat.cc -o /data/download/squid/squid-3.5.25/src/stat.cc.ll
echo "473 /data/download/squid/squid-3.5.25/src/stat.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StatCounters.cc -o /data/download/squid/squid-3.5.25/src/StatCounters.cc.ll
echo "474 /data/download/squid/squid-3.5.25/src/StatCounters.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StatHist.cc -o /data/download/squid/squid-3.5.25/src/StatHist.cc.ll
echo "475 /data/download/squid/squid-3.5.25/src/StatHist.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/String.cc -o /data/download/squid/squid-3.5.25/src/String.cc.ll
echo "476 /data/download/squid/squid-3.5.25/src/String.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StrList.cc -o /data/download/squid/squid-3.5.25/src/StrList.cc.ll
echo "477 /data/download/squid/squid-3.5.25/src/StrList.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/stmem.cc -o /data/download/squid/squid-3.5.25/src/stmem.cc.ll
echo "478 /data/download/squid/squid-3.5.25/src/stmem.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store.cc -o /data/download/squid/squid-3.5.25/src/store.cc.ll
echo "479 /data/download/squid/squid-3.5.25/src/store.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreFileSystem.cc -o /data/download/squid/squid-3.5.25/src/StoreFileSystem.cc.ll
echo "480 /data/download/squid/squid-3.5.25/src/StoreFileSystem.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store_io.cc -o /data/download/squid/squid-3.5.25/src/store_io.cc.ll
echo "481 /data/download/squid/squid-3.5.25/src/store_io.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreIOState.cc -o /data/download/squid/squid-3.5.25/src/StoreIOState.cc.ll
echo "482 /data/download/squid/squid-3.5.25/src/StoreIOState.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store_client.cc -o /data/download/squid/squid-3.5.25/src/store_client.cc.ll
echo "483 /data/download/squid/squid-3.5.25/src/store_client.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store_digest.cc -o /data/download/squid/squid-3.5.25/src/store_digest.cc.ll
echo "484 /data/download/squid/squid-3.5.25/src/store_digest.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store_dir.cc -o /data/download/squid/squid-3.5.25/src/store_dir.cc.ll
echo "485 /data/download/squid/squid-3.5.25/src/store_dir.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store_key_md5.cc -o /data/download/squid/squid-3.5.25/src/store_key_md5.cc.ll
echo "486 /data/download/squid/squid-3.5.25/src/store_key_md5.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store_log.cc -o /data/download/squid/squid-3.5.25/src/store_log.cc.ll
echo "487 /data/download/squid/squid-3.5.25/src/store_log.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store_rebuild.cc -o /data/download/squid/squid-3.5.25/src/store_rebuild.cc.ll
echo "488 /data/download/squid/squid-3.5.25/src/store_rebuild.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store_swapin.cc -o /data/download/squid/squid-3.5.25/src/store_swapin.cc.ll
echo "489 /data/download/squid/squid-3.5.25/src/store_swapin.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store_swapmeta.cc -o /data/download/squid/squid-3.5.25/src/store_swapmeta.cc.ll
echo "490 /data/download/squid/squid-3.5.25/src/store_swapmeta.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/store_swapout.cc -o /data/download/squid/squid-3.5.25/src/store_swapout.cc.ll
echo "491 /data/download/squid/squid-3.5.25/src/store_swapout.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreMetaUnpacker.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaUnpacker.cc.ll
echo "492 /data/download/squid/squid-3.5.25/src/StoreMetaUnpacker.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreMeta.cc -o /data/download/squid/squid-3.5.25/src/StoreMeta.cc.ll
echo "493 /data/download/squid/squid-3.5.25/src/StoreMeta.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreMetaMD5.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaMD5.cc.ll
echo "494 /data/download/squid/squid-3.5.25/src/StoreMetaMD5.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreMetaSTD.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaSTD.cc.ll
echo "495 /data/download/squid/squid-3.5.25/src/StoreMetaSTD.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreMetaSTDLFS.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaSTDLFS.cc.ll
echo "496 /data/download/squid/squid-3.5.25/src/StoreMetaSTDLFS.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreMetaURL.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaURL.cc.ll
echo "497 /data/download/squid/squid-3.5.25/src/StoreMetaURL.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreMetaVary.cc -o /data/download/squid/squid-3.5.25/src/StoreMetaVary.cc.ll
echo "498 /data/download/squid/squid-3.5.25/src/StoreMetaVary.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreStats.cc -o /data/download/squid/squid-3.5.25/src/StoreStats.cc.ll
echo "499 /data/download/squid/squid-3.5.25/src/StoreStats.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/StoreSwapLogData.cc -o /data/download/squid/squid-3.5.25/src/StoreSwapLogData.cc.ll
echo "500 /data/download/squid/squid-3.5.25/src/StoreSwapLogData.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/SwapDir.cc -o /data/download/squid/squid-3.5.25/src/SwapDir.cc.ll
echo "501 /data/download/squid/squid-3.5.25/src/SwapDir.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/Transients.cc -o /data/download/squid/squid-3.5.25/src/Transients.cc.ll
echo "502 /data/download/squid/squid-3.5.25/src/Transients.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/MemStore.cc -o /data/download/squid/squid-3.5.25/src/MemStore.cc.ll
echo "503 /data/download/squid/squid-3.5.25/src/MemStore.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/tools.cc -o /data/download/squid/squid-3.5.25/src/tools.cc.ll
echo "504 /data/download/squid/squid-3.5.25/src/tools.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/tunnel.cc -o /data/download/squid/squid-3.5.25/src/tunnel.cc.ll
echo "505 /data/download/squid/squid-3.5.25/src/tunnel.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/unlinkd.cc -o /data/download/squid/squid-3.5.25/src/unlinkd.cc.ll
echo "506 /data/download/squid/squid-3.5.25/src/unlinkd.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/url.cc -o /data/download/squid/squid-3.5.25/src/url.cc.ll
echo "507 /data/download/squid/squid-3.5.25/src/url.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/urn.cc -o /data/download/squid/squid-3.5.25/src/urn.cc.ll
echo "508 /data/download/squid/squid-3.5.25/src/urn.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/wccp.cc -o /data/download/squid/squid-3.5.25/src/wccp.cc.ll
echo "509 /data/download/squid/squid-3.5.25/src/wccp.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/wccp2.cc -o /data/download/squid/squid-3.5.25/src/wccp2.cc.ll
echo "510 /data/download/squid/squid-3.5.25/src/wccp2.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/whois.cc -o /data/download/squid/squid-3.5.25/src/whois.cc.ll
echo "511 /data/download/squid/squid-3.5.25/src/whois.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/wordlist.cc -o /data/download/squid/squid-3.5.25/src/wordlist.cc.ll
echo "512 /data/download/squid/squid-3.5.25/src/wordlist.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/LoadableModule.cc -o /data/download/squid/squid-3.5.25/src/LoadableModule.cc.ll
echo "513 /data/download/squid/squid-3.5.25/src/LoadableModule.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/LoadableModules.cc -o /data/download/squid/squid-3.5.25/src/LoadableModules.cc.ll
echo "514 /data/download/squid/squid-3.5.25/src/LoadableModules.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModules_gen.cc -o /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModules_gen.cc.ll
echo "515 /data/download/squid/squid-3.5.25/src/DiskIO/DiskIOModules_gen.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/err_type.cc -o /data/download/squid/squid-3.5.25/src/err_type.cc.ll
echo "516 /data/download/squid/squid-3.5.25/src/err_type.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/err_detail_type.cc -o /data/download/squid/squid-3.5.25/src/err_detail_type.cc.ll
echo "517 /data/download/squid/squid-3.5.25/src/err_detail_type.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/globals.cc -o /data/download/squid/squid-3.5.25/src/globals.cc.ll
echo "518 /data/download/squid/squid-3.5.25/src/globals.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/hier_code.cc -o /data/download/squid/squid-3.5.25/src/hier_code.cc.ll
echo "519 /data/download/squid/squid-3.5.25/src/hier_code.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/icp_opcode.cc -o /data/download/squid/squid-3.5.25/src/icp_opcode.cc.ll
echo "520 /data/download/squid/squid-3.5.25/src/icp_opcode.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/LogTags.cc -o /data/download/squid/squid-3.5.25/src/LogTags.cc.ll
echo "521 /data/download/squid/squid-3.5.25/src/LogTags.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/lookup_t.cc -o /data/download/squid/squid-3.5.25/src/lookup_t.cc.ll
echo "522 /data/download/squid/squid-3.5.25/src/lookup_t.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/repl_modules.cc -o /data/download/squid/squid-3.5.25/src/repl_modules.cc.ll
echo "523 /data/download/squid/squid-3.5.25/src/repl_modules.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -DDEFAULT_CONFIG_FILE=\"/usr/local/squid/etc/squid.conf\" -DDEFAULT_SQUID_DATA_DIR=\"/usr/local/squid/share\" -DDEFAULT_SQUID_CONFIG_DIR=\"/usr/local/squid/etc\" -I.. -I../include -I../lib -I../src -I../include -I../src -D_REENTRANT -S /data/download/squid/squid-3.5.25/src/swap_log_op.cc -o /data/download/squid/squid-3.5.25/src/swap_log_op.cc.ll
echo "524 /data/download/squid/squid-3.5.25/src/swap_log_op.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/src/.libs
clang -g -emit-llvm -S /data/download/squid/squid-3.5.25/src/.libs/squidS.c -o /data/download/squid/squid-3.5.25/src/.libs/squidS.c.ll
echo "525 /data/download/squid/squid-3.5.25/src/.libs/squidS.c to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/purge/convert.cc -o /data/download/squid/squid-3.5.25/tools/purge/convert.cc.ll
echo "526 /data/download/squid/squid-3.5.25/tools/purge/convert.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/purge/socket.cc -o /data/download/squid/squid-3.5.25/tools/purge/socket.cc.ll
echo "527 /data/download/squid/squid-3.5.25/tools/purge/socket.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/purge/signal.cc -o /data/download/squid/squid-3.5.25/tools/purge/signal.cc.ll
echo "528 /data/download/squid/squid-3.5.25/tools/purge/signal.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/purge/squid-tlv.cc -o /data/download/squid/squid-3.5.25/tools/purge/squid-tlv.cc.ll
echo "529 /data/download/squid/squid-3.5.25/tools/purge/squid-tlv.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/purge/copyout.cc -o /data/download/squid/squid-3.5.25/tools/purge/copyout.cc.ll
echo "530 /data/download/squid/squid-3.5.25/tools/purge/copyout.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/purge/conffile.cc -o /data/download/squid/squid-3.5.25/tools/purge/conffile.cc.ll
echo "531 /data/download/squid/squid-3.5.25/tools/purge/conffile.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/purge
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/purge/purge.cc -o /data/download/squid/squid-3.5.25/tools/purge/purge.cc.ll
echo "532 /data/download/squid/squid-3.5.25/tools/purge/purge.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/squidclient/gssapi_support.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/gssapi_support.cc.ll
echo "533 /data/download/squid/squid-3.5.25/tools/squidclient/gssapi_support.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/squidclient/Ping.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/Ping.cc.ll
echo "534 /data/download/squid/squid-3.5.25/tools/squidclient/Ping.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/squidclient/squidclient.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/squidclient.cc.ll
echo "535 /data/download/squid/squid-3.5.25/tools/squidclient/squidclient.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/squidclient/stub_debug.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/stub_debug.cc.ll
echo "536 /data/download/squid/squid-3.5.25/tools/squidclient/stub_debug.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/squidclient/test_tools.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/test_tools.cc.ll
echo "537 /data/download/squid/squid-3.5.25/tools/squidclient/test_tools.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/squidclient/time.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/time.cc.ll
echo "538 /data/download/squid/squid-3.5.25/tools/squidclient/time.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools/squidclient
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I../.. -I../../include -I../../lib -I../../src -I../../include -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/squidclient/Transport.cc -o /data/download/squid/squid-3.5.25/tools/squidclient/Transport.cc.ll
echo "539 /data/download/squid/squid-3.5.25/tools/squidclient/Transport.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/cachemgr.cc -o /data/download/squid/squid-3.5.25/tools/cachemgr.cc.ll
echo "540 /data/download/squid/squid-3.5.25/tools/cachemgr.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/MemBuf.cc -o /data/download/squid/squid-3.5.25/tools/MemBuf.cc.ll
echo "541 /data/download/squid/squid-3.5.25/tools/MemBuf.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/stub_cbdata.cc -o /data/download/squid/squid-3.5.25/tools/stub_cbdata.cc.ll
echo "542 /data/download/squid/squid-3.5.25/tools/stub_cbdata.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/stub_debug.cc -o /data/download/squid/squid-3.5.25/tools/stub_debug.cc.ll
echo "543 /data/download/squid/squid-3.5.25/tools/stub_debug.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/stub_mem.cc -o /data/download/squid/squid-3.5.25/tools/stub_mem.cc.ll
echo "544 /data/download/squid/squid-3.5.25/tools/stub_mem.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/test_tools.cc -o /data/download/squid/squid-3.5.25/tools/test_tools.cc.ll
echo "545 /data/download/squid/squid-3.5.25/tools/test_tools.cc to ll" >&2

cd /data/download/squid/squid-3.5.25/tools
clang++ -g -emit-llvm -I/usr/include/c++/4.2.1 -DHAVE_CONFIG_H -I.. -I../include -I../lib -I../src -I../include -I. -DDEFAULT_CACHEMGR_CONFIG=\"/usr/local/squid/etc/cachemgr.conf\" -D_REENTRANT -S /data/download/squid/squid-3.5.25/tools/time.cc -o /data/download/squid/squid-3.5.25/tools/time.cc.ll
echo "546 /data/download/squid/squid-3.5.25/tools/time.cc to ll" >&2
echo "Total ir $total" >&2
echo "Succ ir $succ" >&2
