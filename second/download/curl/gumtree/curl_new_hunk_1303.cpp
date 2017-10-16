"\n"
"       --tftp-no-options\n"
, stdout);
 fputs(
"              (TFTP) Tells curl not to send TFTP options requests.\n"
"\n"
"              This option improves interop with some legacy  servers  that  do\n"
"              not  acknowledge  or  properly implement TFTP options. When this\n"
"              option is used --tftp-blksize is ignored.\n"
"\n"
"              Added in 7.48.0.\n"
"\n"
"       -z, --time-cond <time>\n"
"              (HTTP FTP) Request a file that has been modified later than  the\n"
, stdout);
 fputs(
"              given  time  and date, or one that has been modified before that\n"
"              time. The <date expression> can be all sorts of date strings  or\n"
"              if it doesn't match any internal ones, it is taken as a filename\n"
"              and tries to get  the  modification  date  (mtime)  from  <file>\n"
"              instead.  See  the curl_getdate(3) man pages for date expression\n"
"              details.\n"
"\n"
"              Start the date expression with a dash (-) to make it request for\n"
, stdout);
 fputs(
"              a  document that is older than the given date/time, default is a\n"
"              document that is newer than the specified date/time.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       --tls-max <VERSION>\n"
"              (SSL) VERSION defines maximum supported TLS version.  A  minimum\n"
"              is defined by arguments tlsv1.0 or tlsv1.1 or tlsv1.2.\n"
"\n"
"              default\n"
"                     Use up to recommended TLS version.\n"
"\n"
, stdout);
