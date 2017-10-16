 "              ier  stuff  than  curl would normally do. You should not replace\n"
 , stdout);
  fputs(
 "              internally set  headers  without  knowing  perfectly  well  what\n"
 "              you're  doing. Remove an internal header by giving a replacement\n"
 "              without content on the right  side  of  the  colon,  as  in:  -H\n"
-"              \"Host:\".\n"
+"              \"Host:\".  If  you  send the custom header with no-value then its\n"
+"              header must be terminated with a semicolon, such as  -H  \"X-Cus-\n"
+"              tom-Header;\" to send \"X-Custom-Header:\".\n"
 "\n"
+, stdout);
+ fputs(
 "              curl  will  make  sure  that each header you add/replace is sent\n"
 "              with the proper end-of-line marker, you should thus not add that\n"
 "              as a part of the header content: do not add newlines or carriage\n"
-, stdout);
- fputs(
 "              returns, they will only mess things up for you.\n"
 "\n"
 "              See also the -A, --user-agent and -e, --referer options.\n"
 "\n"
 "              This option can be used  multiple  times  to  add/replace/remove\n"
 "              multiple headers.\n"
 "\n"
+, stdout);
+ fputs(
 "       --hostpubmd5 <md5>\n"
 "              Pass  a  string  containing  32  hexadecimal  digits. The string\n"
 "              should be the 128 bit MD5 checksum of the remote  host's  public\n"
-, stdout);
- fputs(
 "              key,  curl  will  refuse the connection with the host unless the\n"
 "              md5sums match. This option is only for SCP and  SFTP  transfers.\n"
 "              (Added in 7.17.1)\n"
 "\n"
 "       --ignore-content-length\n"
 "              (HTTP)  Ignore  the  Content-Length header. This is particularly\n"
+, stdout);
+ fputs(
 "              useful for servers running Apache 1.x, which will report  incor-\n"
 "              rect Content-Length for files larger than 2 gigabytes.\n"
 "\n"
 "       -i, --include\n"
-, stdout);
- fputs(
 "              (HTTP)  Include  the  HTTP-header in the output. The HTTP-header\n"
 "              includes things like server-name, date of  the  document,  HTTP-\n"
 "              version and more...\n"
 "\n"
 "       -I, --head\n"
 "              (HTTP/FTP/FILE) Fetch the HTTP-header only! HTTP-servers feature\n"
-"              the command HEAD which this uses to get nothing but  the  header\n"
-"              of  a  document.  When used on a FTP or FILE file, curl displays\n"
 , stdout);
  fputs(
+"              the command HEAD which this uses to get nothing but  the  header\n"
+"              of  a  document.  When used on a FTP or FILE file, curl displays\n"
 "              the file size and last modification time only.\n"
 "\n"
 "       --interface <name>\n"
 "              Perform an operation using a specified interface. You can  enter\n"
 "              interface  name,  IP address or host name. An example could look\n"
 "              like:\n"
 "\n"
 "               curl --interface eth0:1 http://www.netscape.com/\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       -j, --junk-session-cookies\n"
-, stdout);
- fputs(
 "              (HTTP) When curl is told to read cookies from a given file, this\n"
 "              option  will  make  it  discard all \"session cookies\". This will\n"
 "              basically have the same effect as if a new session  is  started.\n"
 "              Typical  browsers  always  discard  session cookies when they're\n"
 "              closed down.\n"
 "\n"
 "       -J, --remote-header-name\n"
-"              (HTTP) This option tells the -O, --remote-name option to use the\n"
 , stdout);
  fputs(
+"              (HTTP) This option tells the -O, --remote-name option to use the\n"
 "              server-specified   Content-Disposition   filename   instead   of\n"
 "              extracting a filename from the URL.\n"
 "\n"
 "       -k, --insecure\n"
 "              (SSL) This option explicitly allows curl to  perform  \"insecure\"\n"
 "              SSL connections and transfers. All SSL connections are attempted\n"
 "              to be made secure by using the CA certificate  bundle  installed\n"
-"              by  default.  This  makes  all connections considered \"insecure\"\n"
 , stdout);
  fputs(
+"              by  default.  This  makes  all connections considered \"insecure\"\n"
 "              fail unless -k, --insecure is used.\n"
 "\n"
 "              See    this    online    resource    for    further     details:\n"
 "              http://curl.haxx.se/docs/sslcerts.html\n"
 "\n"
 "       -K, --config <config file>\n"
 "              Specify  which config file to read curl arguments from. The con-\n"
 "              fig file is a text file in which command line arguments  can  be\n"
-"              written  which  then will be used as if they were written on the\n"
 , stdout);
  fputs(
+"              written  which  then will be used as if they were written on the\n"
 "              actual command line. Options and their parameters must be speci-\n"
 "              fied  on  the  same  config  file line, separated by whitespace,\n"
 "              colon, the equals sign or any combination thereof (however,  the\n"
 "              preferred  separator is the equals sign). If the parameter is to\n"
 "              contain  whitespace,  the  parameter  must  be  enclosed  within\n"
-"              quotes. Within double quotes, the following escape sequences are\n"
 , stdout);
  fputs(
+"              quotes. Within double quotes, the following escape sequences are\n"
 "              available: \\\\, \\\", \\t, \\n, \\r and \\v. A backslash preceding  any\n"
 "              other letter is ignored. If the first column of a config line is\n"
 "              a '#' character, the rest of the line will be treated as a  com-\n"
 "              ment.  Only  write  one  option  per physical line in the config\n"
 "              file.\n"
 "\n"
 "              Specify the filename to -K, --config as '-' to  make  curl  read\n"
-"              the file from stdin.\n"
-"\n"
 , stdout);
  fputs(
+"              the file from stdin.\n"
+"\n"
 "              Note  that  to  be able to specify a URL in the config file, you\n"
 "              need to specify it using the --url option,  and  not  by  simply\n"
 "              writing  the  URL  on its own line. So, it could look similar to\n"
 "              this:\n"
 "\n"
 "              url = \"http://curl.haxx.se/docs/\"\n"
