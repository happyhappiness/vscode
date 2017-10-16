       "Options: (H) means HTTP/HTTPS only, (F) means FTP only\n"
       " -a/--append        Append to target file when uploading (F)\n"
       " -A/--user-agent <string> User-Agent to send to server (H)\n"
       " -b/--cookie <name=string/file> Cookie string or file to read cookies from (H)\n"
       " -B/--use-ascii     Use ASCII/text transfer\n",
         curl_version());
  puts(" -C/--continue-at <offset> Specify absolute resume offset\n"
       " -d/--data <data>   HTTP POST data (H)\n"
       "    --data-ascii <data>   HTTP POST ASCII data (H)\n"
       "    --data-binary <data>  HTTP POST binary data (H)\n"
       " -D/--dump-header <file> Write the headers to this file\n"
       "    --egd-file <file> EGD socket path for random data (SSL)\n"
       " -e/--referer       Referer page (H)");
  puts(" -E/--cert <cert[:passwd]> Specifies your certificate file and password (HTTPS)\n"
       "    --cacert <file> CA certifciate to verify peer against (HTTPS)\n"
       "    --connect-timeout <seconds> Maximum time allowed for connection\n"
       " -f/--fail          Fail silently (no output at all) on errors (H)\n"
       " -F/--form <name=content> Specify HTTP POST data (H)\n"
       " -g/--globoff       Disable URL sequences and ranges using {} and []\n"
       " -G/--get           Send the -d data with a HTTP GET (H)\n");
  puts(" -h/--help          This help text\n"
       " -H/--header <line> Custom header to pass to server. (H)"
       " -i/--include       Include the HTTP-header in the output (H)\n"
       " -I/--head          Fetch document info only (HTTP HEAD/FTP SIZE)\n"
       "    --interface <interface> Specify the interface to be used\n"
       "    --krb4 <level>  Enable krb4 with specified security level (F)\n"
       " -K/--config        Specify which config file to read\n"
       " -l/--list-only     List only names of an FTP directory (F)");
