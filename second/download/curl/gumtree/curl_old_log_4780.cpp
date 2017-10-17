fputs(
"              determines the amount.\n"
"\n"
"       --retry-max-time <seconds>\n"
"              The  retry  timer  is  reset  before the first transfer attempt.\n"
"              Retries will be done as usual (see --retry) as long as the timer\n"
"              hasn't reached this given limit. Notice that if the timer hasn't\n"
"              reached the limit, the request will be made and  while  perform-\n"
"              ing,  it may take longer than this given time period. To limit a\n"
, stdout);