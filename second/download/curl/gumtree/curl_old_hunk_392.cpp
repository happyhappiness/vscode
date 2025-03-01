"              -m/--max-time option.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -c/--cookie-jar <file name>\n"
"              Specify to which file you want curl to write all cookies after a\n"
"              completed operation. Curl writes  all  cookies  previously  read\n"
, stdout);
 fputs(
"              from  a  specified  file  as  well  as all cookies received from\n"
"              remote server(s). If no cookies are known, no file will be writ-\n"
"              ten.  The  file  will  be written using the Netscape cookie file\n"
"              format. If you set the file name to  a  single  dash,  \"-\",  the\n"
"              cookies will be written to stdout.\n"
"\n"
"              NOTE If the cookie jar can't be created or written to, the whole\n"
, stdout);
 fputs(
"              curl operation won't fail or even report an error clearly. Using\n"
"              -v  will  get  a warning displayed, but that is the only visible\n"
"              feedback you get about this possibly lethal situation.\n"
"\n"
"              If this option is used several times, the  last  specified  file\n"
"              name will be used.\n"
"\n"
"       -C/--continue-at <offset>\n"
"              Continue/Resume  a  previous  file transfer at the given offset.\n"
, stdout);
 fputs(
"              The given offset is the exact  number  of  bytes  that  will  be\n"
"              skipped,  counting  from the beginning of the source file before\n"
"              it is transferred to the destination.  If used with uploads, the\n"
"              FTP server command SIZE will not be used by curl.\n"
"\n"
"              Use  \"-C  -\" to tell curl to automatically find out where/how to\n"
"              resume the transfer. It then uses the given  output/input  files\n"
"              to figure that out.\n"
"\n"
, stdout);
 fputs(
"              If this option is used several times, the last one will be used.\n"
"\n"
