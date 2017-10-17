fputs(
"              ported in the URL, like this:\n"
"\n"
"               curl --upload-file \"{file1,file2}\" http://www.example.com\n"
"\n"
"              or even\n"
"\n"
"               curl -T \"img[1-1000].png\" ftp://ftp.example.com/upload/\n"
"\n"
"              When uploading to an SMTP server: the uploaded data  is  assumed\n"
"              to be RFC 5322 formatted. It has to feature the necessary set of\n"
"              headers and mail body formatted correctly by the  user  as  curl\n"
, stdout);