fputs(
"                    -F '=)' -F '=@textfile.txt' ...  smtp://example.com\n"
"\n"
"              Data  can  be  encoded  for  transfer  using encoder=. Available\n"
"              encodings are binary and 8bit that do nothing else  than  adding\n"
"              the  corresponding  Content-Transfer-Encoding  header, 7bit that\n"
"              only rejects 8-bit characters with  a  transfer  error,  quoted-\n"
"              printable  and  base64 that encodes data according to the corre-\n"
, stdout);