fputs(
"              This is done by first doing a request and checking the response-\n"
"              headers, thus inducing an extra network round-trip. This is used\n"
"              instead  of  setting a specific authentication method, which you\n"
"              can do with --basic, --digest, --ntlm, and  --negotiate.  (Added\n"
"              in 7.10.6)\n"
"\n"
"              Note  that  using --anyauth is not recommended if you do uploads\n"
"              from stdin, since it may require data to be sent twice and  then\n"
, stdout);