"              # and fetch another URL too\n"
"              url = \"curl.haxx.se/docs/manpage.html\"\n"
"              -O\n"
"              referer = \"http://nowhereatall.com/\"\n"
"              # --- End of example file ---\n"
"\n"
"              This option can be used multiple times to load  multiple  config\n"
"              files.\n"
"\n"
, stdout);
 fputs(
"       --keepalive-time <seconds>\n"
"              This  option  sets  the  time  a connection needs to remain idle\n"
"              before sending keepalive probes and the time between  individual\n"
"              keepalive probes. It is currently effective on operating systems\n"
"              offering  the  TCP_KEEPIDLE  and  TCP_KEEPINTVL  socket  options\n"
"              (meaning  Linux, recent AIX, HP-UX and more). This option has no\n"
"              effect if --no-keepalive is used. (Added in 7.18.0)\n"
"\n"
, stdout);
 fputs(
"              If this option is used several times, the last one will be used.\n"
"              If unspecified, the option defaults to 60 seconds.\n"
