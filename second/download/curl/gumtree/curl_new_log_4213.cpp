fputs(
"              response code or an HTTP 5xx response code.\n"
"\n"
"              When curl is about to retry a transfer, it will first  wait  one\n"
"              second  and  then for all forthcoming retries it will double the\n"
"              waiting time until it reaches 10 minutes which then will be  the\n"
"              delay  between  the rest of the retries.  By using --retry-delay\n"
"              you  disable  this  exponential  backoff  algorithm.  See   also\n"
, stdout);