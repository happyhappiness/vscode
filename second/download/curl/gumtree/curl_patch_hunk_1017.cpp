 "        curl -P 192.168.0.10 ftp.download.com\n"
 "\n"
 "NETWORK INTERFACE\n"
 "\n"
 "  Get a web page from a server using a specified port for the interface:\n"
 "\n"
+, stdout);
+ fputs(
 "        curl --interface eth0:1 http://www.netscape.com/\n"
 "\n"
 "  or\n"
 "\n"
-, stdout);
- fputs(
 "        curl --interface 192.168.1.10 http://www.netscape.com/\n"
 "\n"
 "HTTPS\n"
 "\n"
 "  Secure HTTP requires SSL libraries to be installed and used when curl is\n"
 "  built. If that is done, curl is capable of retrieving and posting documents\n"
