"              --cacert file contains many CA certificates.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -f/--fail\n"
"              (HTTP) Fail silently (no output at all) on server  errors.  This\n"
"              is  mostly done like this to better enable scripts etc to better\n"
, stdout);
 fputs(
"              deal with failed attempts. In normal cases when  a  HTTP  server\n"
"              fails to deliver a document, it returns an HTML document stating\n"
"              so (which often also describes why and  more).  This  flag  will\n"
"              prevent curl from outputting that and return error 22.\n"
"\n"
"              This  method is not fail-safe and there are occasions where non-\n"
"              successful response codes will  slip  through,  especially  when\n"
, stdout);
 fputs(
"              authentication is involved (response codes 401 and 407).\n"
