fputs(
"              with --retry.\n"
"\n"
"              Added in 7.52.0.\n"
"\n"
"       --retry-delay <seconds>\n"
"              Make curl sleep this amount of time before  each  retry  when  a\n"
"              transfer  has  failed  with  a  transient  error (it changes the\n"
"              default backoff time algorithm between retries). This option  is\n"
"              only  interesting if --retry is also used. Setting this delay to\n"
"              zero will make curl use the default backoff time.\n"
"\n"
, stdout);