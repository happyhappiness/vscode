fputs(
"              waiting time until it reaches 10 minutes which then will be  the\n"
"              delay  between  the rest of the retries.  By using --retry-delay\n"
"              you  disable  this  exponential  backoff  algorithm.  See   also\n"
"              --retry-max-time  to  limit  the total time allowed for retries.\n"
"              (Added in 7.12.3)\n"
"\n"
"              If this option is  used  multiple  times,  the  last  occurrence\n"
"              decide the amount.\n"
"\n"
"       --retry-delay <seconds>\n"
, stdout);