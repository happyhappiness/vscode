fputs(
"              (HTTP) Fail silently (no output at all) on server  errors.  This\n"
"              is  mostly done like this to better enable scripts etc to better\n"
"              deal with failed attempts. In normal cases when  a  HTTP  server\n"
"              fails  to deliver a document, it returns a HTML document stating\n"
"              so (which often also describes why and  more).  This  flag  will\n"
"              prevent curl from outputting that and fail silently instead.\n"
"\n"
, stdout);