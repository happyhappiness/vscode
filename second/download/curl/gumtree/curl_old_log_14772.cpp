fputs(
"       -t, --telnet-option <opt=val>\n"
"              Pass options to the telnet protocol. Supported options are:\n"
"\n"
"              TTYPE=<term> Sets the terminal type.\n"
"\n"
"              XDISPLOC=<X display> Sets the X display location.\n"
"\n"
"              NEW_ENV=<var,val> Sets an environment variable.\n"
"\n"
"       --tftp-blksize <value>\n"
"              (TFTP) Set TFTP BLKSIZE option (must be >512). This is the block\n"
"              size that curl will try to use when transferring data to or from\n"
, stdout);