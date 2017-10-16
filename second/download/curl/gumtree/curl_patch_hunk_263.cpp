 "\n"
 "              This option can be used  multiple  times  to  add/replace/remove\n"
 , stdout);
  fputs(
 "              multiple headers.\n"
 "\n"
+"       --hostpubmd5\n"
+"              Pass  a  string  containing  32  hexadecimal  digits. The string\n"
+"              should be the 128 bit MD5 cheksum of the  remote  host’s  public\n"
+"              key,  curl  will  refuse the connection with the host unless the\n"
+"              md5sums match. This option is only for SCP and  SFTP  transfers.\n"
+"              (Added in 7.17.1)\n"
+"\n"
 "       --ignore-content-length\n"
+, stdout);
+ fputs(
 "              (HTTP)  Ignore  the  Content-Length header. This is particularly\n"
 "              useful for servers running Apache 1.x, which will report  incor‐\n"
 "              rect Content-Length for files larger than 2 gigabytes.\n"
 "\n"
 "       -i/--include\n"
 "              (HTTP)  Include  the  HTTP-header in the output. The HTTP-header\n"
 "              includes things like server-name, date of  the  document,  HTTP-\n"
-, stdout);
- fputs(
 "              version and more...\n"
 "\n"
+, stdout);
+ fputs(
 "              If  this  option  is  used  twice, the second will again disable\n"
 "              header include.\n"
 "\n"
 "       --interface <name>\n"
 "              Perform an operation using a specified interface. You can  enter\n"
 "              interface  name,  IP address or host name. An example could look\n"
 "              like:\n"
 "\n"
 "               curl --interface eth0:1 http://www.netscape.com/\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
+"       -I/--head\n"
 , stdout);
  fputs(
-"       -I/--head\n"
 "              (HTTP/FTP/FILE) Fetch the HTTP-header only! HTTP-servers feature\n"
 "              the command HEAD which this uses to get nothing but  the  header\n"
 "              of  a  document.  When used on a FTP or FILE file, curl displays\n"
 "              the file size and last modification time only.\n"
 "\n"
 "              If this option is used twice,  the  second  will  again  disable\n"
