 , stdout);
  fputs(
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 "       --cacert <CA certificate>\n"
 "              (SSL) Tells curl to use the specified certificate file to verify\n"
-"              the peer. The file may contain  multiple  CA  certificates.  The\n"
-"              certificate(s)  must be in PEM format. Normally curl is built to\n"
+"              the  peer.  The  file  may contain multiple CA certificates. The\n"
+"              certificate(s) must be in PEM format. Normally curl is built  to\n"
 "              use a default file for this, so this option is typically used to\n"
 "              alter that default file.\n"
 "\n"
 , stdout);
  fputs(
-"              curl  recognizes the environment variable named 'CURL_CA_BUNDLE'\n"
-"              if it is set, and uses the given path as a path  to  a  CA  cert\n"
+"              curl recognizes the environment variable named  'CURL_CA_BUNDLE'\n"
+"              if  it  is  set,  and uses the given path as a path to a CA cert\n"
 "              bundle. This option overrides that variable.\n"
 "\n"
-"              The  windows  version  of  curl will automatically look for a CA\n"
+"              The windows version of curl will automatically  look  for  a  CA\n"
 "              certs file named 'curl-ca-bundle.crt', either in the same direc-\n"
 "              tory as curl.exe, or in the Current Working Directory, or in any\n"
 "              folder along your PATH.\n"
 "\n"
 , stdout);
  fputs(
-"              If curl is built against the NSS SSL library  then  this  option\n"
-"              tells  curl the nickname of the CA certificate to use within the\n"
-"              NSS database defined by the environment variable SSL_DIR (or  by\n"
-"              default  /etc/pki/nssdb).   If  the NSS PEM PKCS#11 module (lib-\n"
+"              If  curl  is  built against the NSS SSL library then this option\n"
+"              tells curl the nickname of the CA certificate to use within  the\n"
+"              NSS  database defined by the environment variable SSL_DIR (or by\n"
+"              default /etc/pki/nssdb).  If the NSS PEM  PKCS#11  module  (lib-\n"
 "              nsspem.so) is available then PEM files may be loaded.\n"
 "\n"
 "              If this option is used several times, the last one will be used.\n"
 "\n"
 , stdout);
  fputs(
