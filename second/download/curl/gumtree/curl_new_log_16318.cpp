fputs(
"              - a multipart can be terminated with a '=)' argument.\n"
"\n"
"              Example:  the  following  command sends an SMTP mime e-mail con-\n"
"              sisting in an inline part in two alternative formats: plain text\n"
"              and HTML. It attaches a text file:\n"
"\n"
"               curl -F '=(;type=multipart/alternative' \\\n"
"                       -F '=plain text message' \\\n"
"                       -F '= <body>HTML message</body>;type=text/html' \\\n"
, stdout);