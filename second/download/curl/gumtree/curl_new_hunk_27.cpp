"FTP and PATH NAMES\n"
"\n"
"  Do note that when getting files with the ftp:// URL, the given path is\n"
"  relative the directory you enter. To get the file 'README' from your home\n"
"  directory at your ftp site, do:\n"
"\n"
, stdout);
 fputs(
"        curl ftp://user:passwd@my.site.com/README\n"
"\n"
"  But if you want the README file from the root directory of that very same\n"
"  site, you need to specify the absolute file name:\n"
"\n"
"        curl ftp://user:passwd@my.site.com//README\n"
