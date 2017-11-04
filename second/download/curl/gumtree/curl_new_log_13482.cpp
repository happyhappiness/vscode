fputs(
"       --retry <num>\n"
"              If  a  transient  error is returned when curl tries to perform a\n"
"              transfer, it will retry this number of times before  giving  up.\n"
"              Setting  the  number to 0 makes curl do no retries (which is the\n"
"              default). Transient error means either: a timeout,  an  FTP  4xx\n"
"              response code or an HTTP 5xx response code.\n"
"\n"
"              When  curl  is about to retry a transfer, it will first wait one\n"
, stdout);