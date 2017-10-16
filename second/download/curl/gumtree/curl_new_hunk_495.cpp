"              or\n"
"\n"
"              curl -F \"name=daniel;type=text/foo\" url.com\n"
"\n"
, stdout);
 fputs(
"              You  can  also explicitly change the name field of a file upload\n"
"              part by setting filename=, like this:\n"
"\n"
"              curl -F \"file=@localfile;filename=nameinpost\" url.com\n"
"\n"
"              See further examples and details in the MANUAL.\n"
"\n"
