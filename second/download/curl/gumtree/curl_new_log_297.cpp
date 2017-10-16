puts(
" requests. It is If-Modified-Since or If-Unmodified-Since. Curl allow you to\n"
" specify them with the -z/--time-cond flag.\n"
"\n"
" For example, you can easily make a download that only gets performed if the\n"
" remote file is newer than a local copy. It would be made like:\n"
"\n"
"        curl -z local.html http://remote.server.com/remote.html\n"
"\n"
" Or you can download a file only if the local file is newer than the remote\n"
" one. Do this by prepending the date string with a '-', as in:\n"
"\n"
);