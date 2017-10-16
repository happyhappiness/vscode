 "\n"
 "       -R, --remote-time\n"
 "              When used, this will make curl attempt to figure out  the  time-\n"
 "              stamp  of  the  remote  file,  and if that is available make the\n"
 "              local file get that same timestamp.\n"
 "\n"
+"       --request-target\n"
+"              (HTTP) Tells curl to use an alternative \"target\" (path)  instead\n"
+, stdout);
+ fputs(
+"              of  using  the  path as provided in the URL. Particularly useful\n"
+"              when wanting to issue HTTP requests  without  leading  slash  or\n"
+"              other  data  that  doesn't  follow the regular URL pattern, like\n"
+"              \"OPTIONS *\".\n"
+"\n"
 "       -X, --request <command>\n"
 "              (HTTP) Specifies a custom request method to use when communicat-\n"
+"              ing  with the HTTP server.  The specified request method will be\n"
 , stdout);
  fputs(
-"              ing  with the HTTP server.  The specified request method will be\n"
 "              used instead of the method otherwise  used  (which  defaults  to\n"
 "              GET).  Read  the HTTP 1.1 specification for details and explana-\n"
 "              tions. Common additional HTTP requests include PUT  and  DELETE,\n"
 "              but related technologies like WebDAV offers PROPFIND, COPY, MOVE\n"
 "              and more.\n"
 "\n"
 "              Normally you don't need this option. All  sorts  of  GET,  HEAD,\n"
+"              POST and PUT requests are rather invoked by using dedicated com-\n"
 , stdout);
  fputs(
-"              POST and PUT requests are rather invoked by using dedicated com-\n"
 "              mand line options.\n"
 "\n"
 "              This option only changes  the  actual  word  used  in  the  HTTP\n"
 "              request,  it does not alter the way curl behaves. So for example\n"
 "              if you want to make a proper HEAD request, using  -X  HEAD  will\n"
 "              not suffice. You need to use the -I, --head option.\n"
 "\n"
 "              The  method  string  you set with -X, --request will be used for\n"
+"              all requests, which if you for example use  -L,  --location  may\n"
 , stdout);
  fputs(
-"              all requests, which if you for example use  -L,  --location  may\n"
 "              cause  unintended  side-effects when curl doesn't change request\n"
 "              method according to the HTTP 30x response codes - and similar.\n"
 "\n"
 "              (FTP) Specifies a custom FTP command to use instead of LIST when\n"
 "              doing file lists with FTP.\n"
 "\n"
 "              (POP3) Specifies a custom POP3 command to use instead of LIST or\n"
 "              RETR. (Added in 7.26.0)\n"
 "\n"
+"              (IMAP) Specifies a custom IMAP command to use instead  of  LIST.\n"
 , stdout);
  fputs(
-"              (IMAP) Specifies a custom IMAP command to use instead  of  LIST.\n"
 "              (Added in 7.30.0)\n"
 "\n"
 "              (SMTP) Specifies a custom SMTP command to use instead of HELP or\n"
 "              VRFY. (Added in 7.34.0)\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --resolve <host:port:address>\n"
 "              Provide a custom address for a  specific  host  and  port  pair.\n"
+"              Using  this,  you  can make the curl requests(s) use a specified\n"
 , stdout);
  fputs(
-"              Using  this,  you  can make the curl requests(s) use a specified\n"
 "              address and prevent the otherwise normally resolved  address  to\n"
 "              be  used.  Consider it a sort of /etc/hosts alternative provided\n"
 "              on the command line. The port number should be the  number  used\n"
 "              for  the  specific  protocol the host will be used for. It means\n"
 "              you need several entries if you want to provide address for  the\n"
-, stdout);
- fputs(
 "              same host but different ports.\n"
 "\n"
+, stdout);
+ fputs(
 "              The provided address set by this option will be used even if -4,\n"
 "              --ipv4 or -6, --ipv6 is set to make curl use another IP version.\n"
 "              This option can be used many times to add  many  host  names  to\n"
 "              resolve.\n"
 "\n"
 "              Added in 7.21.3.\n"
 "\n"
 "       --retry-connrefused\n"
 "              In  addition to the other conditions, consider ECONNREFUSED as a\n"
+"              transient error too for --retry. This option  is  used  together\n"
 , stdout);
  fputs(
-"              transient error too for --retry. This option  is  used  together\n"
 "              with --retry.\n"
 "\n"
 "              Added in 7.52.0.\n"
 "\n"
 "       --retry-delay <seconds>\n"
 "              Make  curl  sleep  this  amount of time before each retry when a\n"
 "              transfer has failed with  a  transient  error  (it  changes  the\n"
 "              default  backoff time algorithm between retries). This option is\n"
 "              only interesting if --retry is also used. Setting this delay  to\n"
-, stdout);
- fputs(
 "              zero will make curl use the default backoff time.\n"
 "\n"
+, stdout);
+ fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "              Added in 7.12.3.\n"
 "\n"
 "       --retry-max-time <seconds>\n"
 "              The  retry  timer  is  reset  before the first transfer attempt.\n"
 "              Retries will be done as usual (see --retry) as long as the timer\n"
 "              hasn't reached this given limit. Notice that if the timer hasn't\n"
+"              reached the limit, the request will be made and  while  perform-\n"
 , stdout);
  fputs(
-"              reached the limit, the request will be made and  while  perform-\n"
 "              ing,  it may take longer than this given time period. To limit a\n"
 "              single request's maximum time, use  -m,  --max-time.   Set  this\n"
 "              option to zero to not timeout retries.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "              Added in 7.12.3.\n"
 "\n"
 "       --retry <num>\n"
+"              If  a  transient  error is returned when curl tries to perform a\n"
 , stdout);
  fputs(
-"              If  a  transient  error is returned when curl tries to perform a\n"
 "              transfer, it will retry this number of times before  giving  up.\n"
 "              Setting  the  number to 0 makes curl do no retries (which is the\n"
 "              default). Transient error means either: a timeout,  an  FTP  4xx\n"
 "              response code or an HTTP 5xx response code.\n"
 "\n"
 "              When  curl  is about to retry a transfer, it will first wait one\n"
+"              second and then for all forthcoming retries it will  double  the\n"
 , stdout);
  fputs(
-"              second and then for all forthcoming retries it will  double  the\n"
 "              waiting  time until it reaches 10 minutes which then will be the\n"
 "              delay between the rest of the retries.  By  using  --retry-delay\n"
 "              you   disable  this  exponential  backoff  algorithm.  See  also\n"
 "              --retry-max-time to limit the total time allowed for retries.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
-, stdout);
- fputs(
 "              Added in 7.12.3.\n"
 "\n"
 "       --sasl-ir\n"
+, stdout);
+ fputs(
 "              Enable initial response in SASL authentication.\n"
 "\n"
 "              Added in 7.31.0.\n"
 "\n"
 "       --service-name <name>\n"
 "              This option allows you to change the service name for SPNEGO.\n"
