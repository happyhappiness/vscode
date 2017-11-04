fputs(
"              ports \"globbing\" of the -T argument, meaning that you can upload\n"
"              multiple  files  to  a single URL by using the same URL globbing\n"
"              style supported in the URL, like this:\n"
"\n"
"              curl -T \"{file1,file2}\" http://www.uploadtothissite.com\n"
"\n"
"              or even\n"
"\n"
"              curl -T \"img[1-1000].png\" ftp://ftp.picturemania.com/upload/\n"
"\n"
"       --tcp-nodelay\n"
"              Turn on the TCP_NODELAY option. See the curl_easy_setopt(3)  man\n"
, stdout);