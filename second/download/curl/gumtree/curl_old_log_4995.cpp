fputs(
"              --negotiate.\n"
"\n"
"              Note  that  using --anyauth is not recommended if you do uploads\n"
"              from stdin, since it may require data to be sent twice and  then\n"
"              the client must be able to rewind. If the need should arise when\n"
"              uploading from stdin, the upload operation will fail.\n"
"\n"
"       -b/--cookie <name=data>\n"
"              (HTTP) Pass the data to the HTTP server as a cookie. It is  sup-\n"
, stdout);