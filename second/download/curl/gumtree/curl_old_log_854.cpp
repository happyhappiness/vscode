fputs(
"              pair specifies what to upload and  to  where.  curl\n"
"              also  supports \"globbing\" of the -T argument, mean-\n"
"              ing that you can upload multiple files to a  single\n"
"              URL  by using the same URL globbing style supported\n"
"              in the URL, like this:\n"
"\n"
"              curl    -T    \"{file1,file2}\"    http://www.upload-\n"
"              tothissite.com\n"
"\n"
"              or even\n"
"\n"
"              curl   -T   \"img[1-1000].png\"  ftp://ftp.picturema-\n"
, stdout);