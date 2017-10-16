fputs(
"        curl -z local.html http://remote.server.com/remote.html\n"
"\n"
" Or you can download a file only if the local file is newer than the remote\n"
" one. Do this by prepending the date string with a '-', as in:\n"
"\n"
"        curl -z -local.html http://remote.server.com/remote.html\n"
"\n"
" You can specify a \"free text\" date as condition. Tell curl to only download\n"
" the file if it was updated since January 12, 2012:\n"
"\n"
"        curl -z \"Jan 12 2012\" http://remote.server.com/remote.html\n"
"\n"
, stdout);