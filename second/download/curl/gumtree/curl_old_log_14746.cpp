fputs(
"              zero will make curl use the default backoff time.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"              Added in 7.12.3.\n"
"\n"
"       --retry-max-time <seconds>\n"
"              The retry timer is reset  before  the  first  transfer  attempt.\n"
"              Retries will be done as usual (see --retry) as long as the timer\n"
"              hasn't reached this given limit. Notice that if the timer hasn't\n"
, stdout);