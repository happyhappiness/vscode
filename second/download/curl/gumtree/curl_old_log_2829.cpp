fputs(
"              --retry-max-time  to  limit  the total time allowed for retries.\n"
"              (Added in 7.12.3)\n"
"\n"
"              If this option is  used  multiple  times,  the  last  occurrence\n"
"              decide the amount.\n"
"\n"
"       --retry-delay <seconds>\n"
"              Make  curl  sleep  this amount of time between each retry when a\n"
"              transfer has failed with  a  transient  error  (it  changes  the\n"
"              default  backoff time algorithm between retries). This option is\n"
, stdout);