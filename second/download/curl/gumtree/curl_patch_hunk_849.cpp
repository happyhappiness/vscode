 "\n"
 , stdout);
  fputs(
 "              If this option is set, the default capath value will be ignored,\n"
 "              and if it is used several times, the last one will be used.\n"
 "\n"
+"       --pinnedpubkey <pinned public key>\n"
+"              (SSL)  Tells curl to use the specified public key file to verify\n"
+"              the peer. The file must contain a single public key in DER  for-\n"
+"              mat.\n"
+"\n"
+"              When  negotiating  a  TLS  or SSL connection, the server sends a\n"
+, stdout);
+ fputs(
+"              certificate indicating its identity. A public key  is  extracted\n"
+"              from  this certificate and if it does not exactly match the pub-\n"
+"              lic key provided to this option, curl will abort the  connection\n"
+"              before sending or receiving any data.\n"
+"\n"
+"              This  is  currently  only  implemented in the OpenSSL and GnuTLS\n"
+"              backends.\n"
+"\n"
+"              If this option is used several times, the last one will be used.\n"
+, stdout);
+ fputs(
+"              (Added in 7.39.0)\n"
+"\n"
 "       -f, --fail\n"
 "              (HTTP)  Fail  silently (no output at all) on server errors. This\n"
 "              is mostly done to better enable scripts etc to better deal  with\n"
 "              failed  attempts.  In  normal cases when an HTTP server fails to\n"
 "              deliver a document, it  returns  an  HTML  document  stating  so\n"
+"              (which  often  also describes why and more). This flag will pre-\n"
 , stdout);
  fputs(
-"              (which  often  also describes why and more). This flag will pre-\n"
 "              vent curl from outputting that and return error 22.\n"
 "\n"
 "              This method is not fail-safe and there are occasions where  non-\n"
 "              successful  response  codes  will  slip through, especially when\n"
 "              authentication is involved (response codes 401 and 407).\n"
 "\n"
 "       -F, --form <name=content>\n"
 "              (HTTP) This lets curl emulate a filled-in form in which  a  user\n"
+"              has  pressed  the  submit  button. This causes curl to POST data\n"
 , stdout);
  fputs(
-"              has  pressed  the  submit  button. This causes curl to POST data\n"
 "              using the  Content-Type  multipart/form-data  according  to  RFC\n"
 "              2388.  This  enables uploading of binary files etc. To force the\n"
 "              'content' part to be a file, prefix the  file  name  with  an  @\n"
 "              sign.  To just get the content part from a file, prefix the file\n"
 "              name with the symbol <. The difference between @ and <  is  then\n"
+"              that  @  makes a file get attached in the post as a file upload,\n"
 , stdout);
  fputs(
-"              that  @  makes a file get attached in the post as a file upload,\n"
 "              while the < makes a text field and just  get  the  contents  for\n"
 "              that text field from a file.\n"
 "\n"
 "              Example,  to send your password file to the server, where 'pass-\n"
 "              word' is the name of the form-field to which /etc/passwd will be\n"
 "              the input:\n"
 "\n"
 "              curl -F password=@/etc/passwd www.mypasswords.com\n"
 "\n"
+"              To read content from stdin instead of a file, use - as the file-\n"
 , stdout);
  fputs(
-"              To read content from stdin instead of a file, use - as the file-\n"
 "              name. This goes for both @ and < constructs.\n"
 "\n"
 "              You can also  tell  curl  what  Content-Type  to  use  by  using\n"
 "              'type=', in a manner similar to:\n"
 "\n"
 "              curl -F \"web=@index.html;type=text/html\" url.com\n"
 "\n"
 "              or\n"
 "\n"
 "              curl -F \"name=daniel;type=text/foo\" url.com\n"
 "\n"
 "              You  can  also explicitly change the name field of a file upload\n"
-, stdout);
- fputs(
 "              part by setting filename=, like this:\n"
 "\n"
+, stdout);
+ fputs(
 "              curl -F \"file=@localfile;filename=nameinpost\" url.com\n"
 "\n"
 "              If filename/path contains ',' or ';', it must be quoted by  dou-\n"
 "              ble-quotes like:\n"
 "\n"
 "              curl -F \"file=@\\\"localfile\\\";filename=\\\"nameinpost\\\"\" url.com\n"
