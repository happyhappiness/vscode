fputs(
"              delay between the rest of the retries.  By  using  --retry-delay\n"
"              you   disable  this  exponential  backoff  algorithm.  See  also\n"
"              --retry-max-time to limit the total time  allowed  for  retries.\n"
"              (Option added in 7.12.3)\n"
"\n"
"              If  this  option  is  used  multiple  times, the last occurrence\n"
"              decide the amount.\n"
"\n"
"       --retry-delay <seconds>\n"
"              Make curl sleep this amount of time between each  retry  when  a\n"
, stdout);