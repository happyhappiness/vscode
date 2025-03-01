"  or\n"
"\n"
"	curl --interface 192.168.1.10 http://www.netscape.com/\n"
"\n"
"HTTPS\n"
"\n"
"  Secure HTTP requires SSL libraries to be installed and used when curl is\n"
"  built. If that is done, curl is capable of retrieving and posting documents\n"
"  using the HTTPS procotol.\n"
"\n"
"  Example:\n"
"\n"
"        curl https://www.secure-site.com\n"
"\n"
);
 puts(
"  Curl is also capable of using your personal certificates to get/post files\n"
"  from sites that require valid certificates. The only drawback is that the\n"
"  certificate needs to be in PEM-format. PEM is a standard and open format to\n"
"  store certificates with, but it is not used by the most commonly used\n"
"  browsers (Netscape and MSEI both use the so called PKCS#12 format). If you\n"
"  want curl to use the certificates you use with your (favourite) browser, you\n"
);
 puts(
"  may need to download/compile a converter that can convert your browser's\n"
"  formatted certificates to PEM formatted ones. This kind of converter is\n"
"  included in recent versions of OpenSSL, and for older versions Dr Stephen\n"
"  N. Henson has written a patch for SSLeay that adds this functionality. You\n"
"  can get his patch (that requires an SSLeay installation) from his site at:\n"
"  http://www.drh-consultancy.demon.co.uk/\n"
"\n"
);
 puts(
"  Example on how to automatically retrieve a document using a certificate with\n"
"  a personal password:\n"
"\n"
"        curl -E /path/to/cert.pem:password https://secure.site.com/\n"
"\n"
"  If you neglect to specify the password on the command line, you will be\n"
"  prompted for the correct password before any data can be received.\n"
"\n"
"  Many older SSL-servers have problems with SSLv3 or TLS, that newer versions\n"
"  of OpenSSL etc is using, therefore it is sometimes useful to specify what\n"
);
 puts(
"  SSL-version curl should use. Use -3 or -2 to specify that exact SSL version\n"
"  to use:\n"
"\n"
"        curl -2 https://secure.site.com/\n"
"\n"
"  Otherwise, curl will first attempt to use v3 and then v2.\n"
"\n"
"  To use OpenSSL to convert your favourite browser's certificate into a PEM\n"
"  formatted one that curl can use, do something like this (assuming netscape,\n"
"  but IE is likely to work similarly):\n"
"\n"
"    You start with hitting the 'security' menu button in netscape. \n"
"\n"
);
 puts(
"    Select 'certificates->yours' and then pick a certificate in the list \n"
"\n"
"    Press the 'export' button \n"
"\n"
"    enter your PIN code for the certs \n"
"\n"
"    select a proper place to save it \n"
"\n"
"    Run the 'openssl' application to convert the certificate. If you cd to the\n"
"    openssl installation, you can do it like:\n"
"\n"
"     # ./apps/openssl pkcs12 -certfile [file you saved] -out [PEMfile]\n"
"\n"
"\n"
"RESUMING FILE TRANSFERS\n"
"\n"
" To continue a file transfer where it was previously aborted, curl supports\n"
);
 puts(
" resume on http(s) downloads as well as ftp uploads and downloads.\n"
"\n"
" Continue downloading a document:\n"
"\n"
"        curl -c -o file ftp://ftp.server.com/path/file\n"
"\n"
" Continue uploading a document(*1):\n"
"\n"
"        curl -c -T file ftp://ftp.server.com/path/file\n"
"\n"
" Continue downloading a document from a web server(*2):\n"
"\n"
"        curl -c -o file http://www.server.com/\n"
"\n"
" (*1) = This requires that the ftp server supports the non-standard command\n"
"        SIZE. If it doesn't, curl will say so.\n"
"\n"
);
 puts(
" (*2) = This requires that the web server supports at least HTTP/1.1. If it\n"
"        doesn't, curl will say so.\n"
"\n"
"TIME CONDITIONS\n"
"\n"
" HTTP allows a client to specify a time condition for the document it\n"
" requests. It is If-Modified-Since or If-Unmodified-Since. Curl allow you to\n"
" specify them with the -z/--time-cond flag.\n"
"\n"
" For example, you can easily make a download that only gets performed if the\n"
" remote file is newer than a local copy. It would be made like:\n"
"\n"
);
 puts(
"        curl -z local.html http://remote.server.com/remote.html\n"
"\n"
" Or you can download a file only if the local file is newer than the remote\n"
" one. Do this by prepending the date string with a '-', as in:\n"
"\n"
"        curl -z -local.html http://remote.server.com/remote.html\n"
"\n"
" You can specify a \"free text\" date as condition. Tell curl to only download\n"
" the file if it was updated since yesterday:\n"
"\n"
"        curl -z yesterday http://remote.server.com/remote.html\n"
"\n"
);
 puts(
" Curl will then accept a wide range of date formats. You always make the date\n"
" check the other way around by prepending it with a dash '-'.\n"
"\n"
"DICT\n"
"\n"
"  For fun try\n"
"\n"
"        curl dict://dict.org/m:curl\n"
"        curl dict://dict.org/d:heisenbug:jargon\n"
"        curl dict://dict.org/d:daniel:web1913\n"
"\n"
"  Aliases for 'm' are 'match' and 'find', and aliases for 'd' are 'define'\n"
"  and 'lookup'. For example,\n"
"\n"
"        curl dict://dict.org/find:curl\n"
"\n"
);
 puts(
"  Commands that break the URL description of the RFC (but not the DICT\n"
"  protocol) are\n"
"\n"
"        curl dict://dict.org/show:db\n"
"        curl dict://dict.org/show:strat\n"
"\n"
