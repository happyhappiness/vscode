fputs(
"              sponding schemes, limiting lines length to 76 characters.\n"
"\n"
"              Example: send multipart mail with a quoted-printable  text  mes-\n"
"              sage and a base64 attached file:\n"
"\n"
"               curl -F '=text message;encoder=quoted-printable' \\\n"
"                    -F '=@localfile;encoder=base64' ... smtp://example.com\n"
"\n"
"              See further examples and details in the MANUAL.\n"
"\n"
"              This option can be used multiple times.\n"
"\n"
, stdout);