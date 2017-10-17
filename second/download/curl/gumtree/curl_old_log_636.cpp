fputs(
"              download. If the file requested is larger than this\n"
"              value,  the  transfer  will not start and curl will\n"
"              return with exit code 63.\n"
"\n"
"              NOTE: The file size is not always  known  prior  to\n"
"              download,  and  for  such  files this option has no\n"
"              effect even if the  file  transfer  ends  up  being\n"
"              larger  than  this  given limit. This concerns both\n"
"              FTP and HTTP transfers.\n"
, stdout);