fputs(
"              --negotiate.\n"
"\n"
"              Using --anyauth is not recommended if you do uploads from stdin,\n"
"              since  it  may require data to be sent twice and then the client\n"
"              must be able to rewind. If the need should arise when  uploading\n"
"              from stdin, the upload operation will fail.\n"
"\n"
"              Used together with -u, --user.\n"
"\n"
"              See also --proxy-anyauth and --basic and --digest.\n"
"\n"
"       -a, --append\n"
, stdout);