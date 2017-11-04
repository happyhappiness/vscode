static void help(void)
{
  printf(CURL_ID "%s\n"
       "Usage: curl [options...] <url>\n"
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
  puts(" -L/--location      Follow Location: hints (H)\n"
       " -m/--max-time <seconds> Maximum time allowed for the transfer\n"
       " -M/--manual        Display huge help text\n"
       " -n/--netrc         Read .netrc for user name and password\n"
       " -N/--no-buffer     Disables the buffering of the output stream");
  puts(" -o/--output <file> Write output to <file> instead of stdout\n"
       " -O/--remote-name   Write output to a file named as the remote file\n"
       " -p/--proxytunnel   Perform non-HTTP services through a HTTP proxy\n"
       " -P/--ftpport <address> Use PORT with address instead of PASV when ftping (F)\n"
       " -q                 When used as the first parameter disables .curlrc\n"
       " -Q/--quote <cmd>   Send QUOTE command to FTP before file transfer (F)");
  puts(" -r/--range <range> Retrieve a byte range from a HTTP/1.1 or FTP server\n"
       " -s/--silent        Silent mode. Don't output anything\n"
       " -S/--show-error    Show error. With -s, make curl show errors when they occur\n"
       "    --stderr <file> Where to redirect stderr. - means stdout.\n"
       " -t/--telnet-option <OPT=val> Set telnet option\n"
       " -T/--upload-file <file> Transfer/upload <file> to remote site\n"
       "    --url <URL>     Another way to specify URL to work with");
  puts(" -u/--user <user[:password]> Specify user and password to use\n"
       " -U/--proxy-user <user[:password]> Specify Proxy authentication\n"
       " -v/--verbose       Makes the operation more talkative\n"
       " -V/--version       Outputs version number then quits\n"
       " -w/--write-out [format] What to output after completion\n"
       " -x/--proxy <host[:port]>  Use proxy. (Default port is 1080)\n"
       "    --random-file <file> File to use for reading random data from (SSL)\n"
       " -X/--request <command> Specific request command to use");
  puts(" -y/--speed-time    Time needed to trig speed-limit abort. Defaults to 30\n"
       " -Y/--speed-limit   Stop transfer if below speed-limit for 'speed-time' secs\n"
       " -z/--time-cond <time> Includes a time condition to the server (H)\n"
       " -Z/--max-redirs <num> Set maximum number of redirections allowed (H)\n"
       " -2/--sslv2         Force usage of SSLv2 (H)\n"
       " -3/--sslv3         Force usage of SSLv3 (H)");
  puts(" -#/--progress-bar  Display transfer progress as a progress bar\n"
       "    --crlf          Convert LF to CRLF in upload. Useful for MVS (OS/390)");
}