 "\n"
 "              If this option is set more than once, the last one will  be  the\n"
 "              one that's used.\n"
 "\n"
 "       --anyauth\n"
 "              (HTTP) Tells curl to figure out authentication method by itself,\n"
-"              and use the most secure one the remote site claims it  supports.\n"
+"              and use the most secure one the remote site claims  to  support.\n"
 "              This is done by first doing a request and checking the response-\n"
 , stdout);
  fputs(
 "              headers, thus possibly inducing  an  extra  network  round-trip.\n"
 "              This  is  used  instead  of  setting  a  specific authentication\n"
 "              method, which you can do with  --basic,  --digest,  --ntlm,  and\n"
