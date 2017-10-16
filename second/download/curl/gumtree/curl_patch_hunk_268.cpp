 "USING PASSWORDS\n"
 "\n"
 " FTP\n"
 "\n"
 "   To ftp files using name+passwd, include them in the URL like:\n"
 "\n"
-, stdout);
- fputs(
 "        curl ftp://name:passwd@machine.domain:port/full/path/to/file\n"
 "\n"
 "   or specify them with the -u flag like\n"
 "\n"
+, stdout);
+ fputs(
 "        curl -u name:passwd ftp://machine.domain:port/full/path/to/file\n"
 "\n"
 " FTPS\n"
 "\n"
 "   It is just like for FTP, but you may also want to specify and use\n"
 "   SSL-specific options for certificates etc.\n"
