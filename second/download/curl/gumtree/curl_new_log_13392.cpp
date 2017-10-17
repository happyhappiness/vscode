fputs(
"              # curl -H \"X-First-Name: Joe\" http://example.com/\n"
"\n"
"              WARNING: headers set  with  this  option  will  be  set  in  all\n"
"              requests  -  even  after  redirects are followed, like when told\n"
"              with -L, --location. This can lead to the header being  sent  to\n"
"              other  hosts than the original host, so sensitive headers should\n"
"              be used with caution combined with following redirects.\n"
"\n"
, stdout);