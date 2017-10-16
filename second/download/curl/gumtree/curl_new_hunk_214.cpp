, stdout);
 fputs(
"       If you want a progress meter for HTTP POST or PUT requests, you need to\n"
"       redirect  the  response  output to a file, using shell redirect (>), -o\n"
"       [file] or similar.\n"
"\n"
"       It is not the same case for FTP upload as that operation is  not  spit‐\n"
"       ting out any response data to the terminal.\n"
"\n"
"       If you prefer a progress \"bar\" instead of the regular meter, -# is your\n"
"       friend.\n"
"OPTIONS\n"
"       -a/--append\n"
, stdout);
 fputs(
"              (FTP) When used in an FTP upload, this will tell curl to  append\n"
"              to  the  target  file  instead  of  overwriting  it. If the file\n"
"              doesn’t exist, it will be created.\n"
"\n"
"              If this option is used twice, the second one will disable append\n"
"              mode again.\n"
"\n"
"       -A/--user-agent <agent string>\n"
"              (HTTP) Specify the User-Agent string to send to the HTTP server.\n"
