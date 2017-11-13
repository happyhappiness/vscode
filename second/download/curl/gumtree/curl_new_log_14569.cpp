fputs(
"               curl -T \"img[1-1000].png\" ftp://ftp.example.com/upload/\n"
"\n"
"              When uploading to an SMTP server: the uploaded data  is  assumed\n"
"              to be RFC 5322 formatted. It has to feature the necessary set of\n"
"              headers and mail body formatted correctly by the  user  as  curl\n"
"              will not transcode nor encode it further in any way.\n"
"\n"
"       --url <url>\n"
"              Specify  a  URL  to  fetch. This option is mostly handy when you\n"
, stdout);