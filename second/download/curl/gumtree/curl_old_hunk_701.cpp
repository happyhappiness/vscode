, stdout);
 fputs(
"              you   disable  this  exponential  backoff  algorithm.  See  also\n"
"              --retry-max-time to limit the total time  allowed  for  retries.\n"
"              (Added in 7.12.3)\n"
"\n"
"              If  this  option  is  used  multiple  times, the last occurrence\n"
"              determines the amount.\n"
"\n"
"       --retry-delay <seconds>\n"
"              Make curl sleep this amount of time before  each  retry  when  a\n"
"              transfer  has  failed  with  a  transient  error (it changes the\n"
, stdout);
 fputs(
"              default backoff time algorithm between retries). This option  is\n"
"              only  interesting if --retry is also used. Setting this delay to\n"
"              zero will make curl use the default  backoff  time.   (Added  in\n"
"              7.12.3)\n"
"\n"
"              If  this  option  is  used  multiple  times, the last occurrence\n"
"              determines the amount.\n"
"\n"
"       --retry-max-time <seconds>\n"
"              The retry timer is reset  before  the  first  transfer  attempt.\n"
, stdout);
 fputs(
"              Retries will be done as usual (see --retry) as long as the timer\n"
