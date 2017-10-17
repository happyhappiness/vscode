fputs(
"              Specify  the  maximum  size (in bytes) of a file to download. If\n"
"              the file requested is larger than this value, the transfer  will\n"
"              not start and curl will return with exit code 63.\n"
"\n"
"              NOTE:  The  file size is not always known prior to download, and\n"
"              for such files this option has no effect even if the file trans‐\n"
"              fer  ends  up  being larger than this given limit. This concerns\n"
, stdout);