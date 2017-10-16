"       -I, --head\n"
"              (HTTP FTP FILE) Fetch the headers only! HTTP-servers feature the\n"
"              command HEAD which this uses to get nothing but the header of  a\n"
"              document.  When  used  on an FTP or FILE file, curl displays the\n"
"              file size and last modification time only.\n"
"\n"
"       -H, --header <header>\n"
"              (HTTP) Extra header to include in the request when sending  HTTP\n"
, stdout);
 fputs(
"              to  a  server. You may specify any number of extra headers. Note\n"
"              that if you should add a custom header that has the same name as\n"
"              one  of  the  internal  ones curl would use, your externally set\n"
