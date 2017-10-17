fputs(
"              only interesting if --retry is also used. Setting this delay  to\n"
"              zero  will  make  curl  use the default backoff time.  (Added in\n"
"              7.12.3)\n"
"\n"
"              If this option is  used  multiple  times,  the  last  occurrence\n"
"              decide the amount.\n"
"\n"
"       --retry-max-time <seconds>\n"
"              The  retry  timer  is  reset  before the first transfer attempt.\n"
"              Retries will be done as usual (see --retry) as long as the timer\n"
, stdout);