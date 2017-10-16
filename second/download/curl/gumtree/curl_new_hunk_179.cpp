"              waiting time until it reaches 10 minutes which then will be  the\n"
, stdout);
 fputs(
"              delay  between  the rest of the retries.  By using --retry-delay\n"
"              you  disable  this  exponential  backoff  algorithm.  See   also\n"
"              --retry-max-time  to  limit  the total time allowed for retries.\n"
"              (Added in 7.12.3)\n"
"\n"
"              If this option is  used  multiple  times,  the  last  occurrence\n"
"              decide the amount.\n"
"\n"
"       --retry-delay <seconds>\n"
"              Make  curl  sleep  this amount of time between each retry when a\n"
, stdout);
 fputs(
"              transfer has failed with  a  transient  error  (it  changes  the\n"
"              default  backoff time algorithm between retries). This option is\n"
"              only interesting if --retry is also used. Setting this delay  to\n"
"              zero  will  make  curl  use the default backoff time.  (Added in\n"
"              7.12.3)\n"
"\n"
"              If this option is  used  multiple  times,  the  last  occurrence\n"
"              decide the amount.\n"
"\n"
"       --retry-max-time <seconds>\n"
, stdout);
