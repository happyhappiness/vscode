"\n"
"              If you use an SSPI-enabled curl binary and perform NTLM  authen-\n"
"              tication,  you  can force curl to select the user name and pass-\n"
"              word from your environment by simply specifying a  single  colon\n"
, stdout);
 fputs(
"              with  this  option: \"-u :\" or by specifying the login options on\n"
"              their own, for example \"-u ;auth=NTLM\".\n"
"\n"
"              You can use the optional login options part to specify  protocol\n"
"              specific  options  that  may  be  used during authentication. At\n"
"              present only IMAP, POP3 and SMTP support login options  as  part\n"
"              of  the  user  login information. For more information about the\n"
