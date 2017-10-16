"       speak FTP.\n"
"\n"
"       curl will do its best to use what you pass to it as a URL.  It  is  not\n"
"       trying  to  validate it as a syntactically correct URL by any means but\n"
"       is instead very liberal with what it accepts.\n"
"\n"
"       curl will attempt to re-use connections for multiple file transfers, so\n"
"       that  getting many files from the same server will not do multiple con-\n"
, stdout);
 fputs(
"       nects / handshakes. This improves speed. Of course this is only done on\n"
"       files  specified  on  a  single command line and cannot be used between\n"
"       separate curl invokes.\n"
