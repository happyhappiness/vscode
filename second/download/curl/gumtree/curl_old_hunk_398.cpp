"              (GSS-Negotiate) support. This is not very common. Use  -V/--ver-\n"
"              sion to see if your curl supports it.\n"
"\n"
"              If this option is used several times, the last one will be used.\n"
"\n"
"       -K/--config <config file>\n"
"              Specify which config file to read curl arguments from. The  con-\n"
"              fig  file  is a text file in which command line arguments can be\n"
"              written which then will be used as if they were written  on  the\n"
, stdout);
 fputs(
"              actual command line. Options and their parameters must be speci-\n"
"              fied on the same config  file  line,  separated  by  whitespace,\n"
"              colon,  the equals sign or any combination thereof (however, the\n"
"              preferred separator is the equals sign). If the parameter is  to\n"
"              contain  whitespace,  the  parameter  must  be  enclosed  within\n"
"              quotes. Within double quotes, the following escape sequences are\n"
, stdout);
 fputs(
"              available:  \\\\, \\\", \\t, \\n, \\r and \\v. A backslash preceding any\n"
"              other letter is ignored. If the first column of a config line is\n"
"              a  '#' character, the rest of the line will be treated as a com-\n"
"              ment. Only write one option per  physical  line  in  the  config\n"
"              file.\n"
"\n"
"              Specify the filename to -K/--config as '-' to make curl read the\n"
"              file from stdin.\n"
"\n"
, stdout);
 fputs(
"              Note that to be able to specify a URL in the  config  file,  you\n"
"              need  to  specify  it  using the --url option, and not by simply\n"
"              writing the URL on its own line. So, it could  look  similar  to\n"
"              this:\n"
"\n"
"              url = \"http://curl.haxx.se/docs/\"\n"
"\n"
"              Long  option  names  can  optionally be given in the config file\n"
"              without the initial double dashes.\n"
"\n"
, stdout);
 fputs(
"              When curl is invoked, it always (unless -q is used) checks for a\n"
"              default  config  file  and  uses it if found. The default config\n"
"              file is checked for in the following places in this order:\n"
"\n"
"              1) curl tries to find the \"home dir\": It first  checks  for  the\n"
"              CURL_HOME and then the HOME environment variables. Failing that,\n"
"              it uses getpwuid() on UNIX-like systems (which returns the  home\n"
, stdout);
 fputs(
"              dir  given the current user in your system). On Windows, it then\n"
"              checks for the APPDATA variable, or as a last resort the '%USER-\n"
"              PROFILE%\\Application Data'.\n"
"\n"
"              2)  On  windows, if there is no _curlrc file in the home dir, it\n"
"              checks for one in the same dir the curl executable is placed. On\n"
"              UNIX-like  systems,  it will simply try to load .curlrc from the\n"
"              determined home dir.\n"
"\n"
, stdout);
 fputs(
"              # --- Example file ---\n"
"              # this is a comment\n"
