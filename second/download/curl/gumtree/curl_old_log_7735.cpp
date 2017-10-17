fputs(
"       The environment variables can be specified in lower case or upper case.\n"
"       The lower case version has precedence. http_proxy is an exception as it\n"
"       is only available in lower case.\n"
"\n"
"       Using  an  environment variable to set the proxy has the same effect as\n"
"       using the --proxy option.\n"
"\n"
"       http_proxy [protocol://]<host>[:port]\n"
"              Sets the proxy server to use for HTTP.\n"
"       HTTPS_PROXY [protocol://]<host>[:port]\n"
, stdout);