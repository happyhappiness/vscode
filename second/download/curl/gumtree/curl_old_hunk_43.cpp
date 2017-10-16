  if(fmt) {
    va_start(ap, fmt);
    fputs("curl: ", stderr); /* prefix it */
    vfprintf(stderr, fmt, ap);
    va_end(ap);
  }
  fprintf(stderr, "curl: try 'curl --help' for more information\n");
}

/*
 * A chain of these nodes contain URL to get and where to put the URL's
 * contents.
 */
struct getout {
  struct getout *next;
  char *url;
  char *outfile;
  int flags;
};
#define GETOUT_OUTFILE (1<<0) /* set when outfile is deemed done */
#define GETOUT_URL     (1<<1) /* set when URL is deemed done */
#define GETOUT_USEREMOTE (1<<2) /* use remote file name locally */

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
  puts(" -c/--cookie-jar <file> Write all cookies to this file after operation (H)\n"
       " -C/--continue-at <offset> Specify absolute resume offset\n"
       " -d/--data <data>   HTTP POST data (H)\n"
       "    --data-ascii <data>   HTTP POST ASCII data (H)\n"
       "    --data-binary <data>  HTTP POST binary data (H)\n"
       "    --disable-epsv  Prevents curl from using EPSV (F)\n"
       " -D/--dump-header <file> Write the headers to this file\n"
       "    --egd-file <file> EGD socket path for random data (SSL)\n"
#ifdef USE_ENVIRONMENT
       "    --environment   Write result codes to environment variables (RISC OS)\n"
#endif
       " -e/--referer       Referer page (H)");
  puts(" -E/--cert <cert[:passwd]> Specifies your certificate file and password (HTTPS)\n"
       "    --cert-type <type> Specifies certificate file type (DER/PEM/ENG) (HTTPS)\n"
       "    --key <key>     Specifies private key file (HTTPS)\n"
       "    --key-type <type> Specifies private key  file type (DER/PEM/ENG) (HTTPS)\n"
       "    --pass  <pass>  Specifies passphrase for the private key (HTTPS)");
  puts("    --engine <eng>  Specifies the crypto engine to use (HTTPS)\n"
       "    --cacert <file> CA certifciate to verify peer against (SSL)\n"
       "    --capath <directory> CA directory (made using c_rehash) to verify\n"
       "                    peer against (SSL)\n"
       "    --ciphers <list> What SSL ciphers to use (SSL)\n"
       "    --compressed    Request a compressed response (using deflate).");
  puts("    --connect-timeout <seconds> Maximum time allowed for connection\n"
       "    --create-dirs   Create the necessary local directory hierarchy\n"
       "    --crlf          Convert LF to CRLF in upload. Useful for MVS (OS/390)\n"
       " -f/--fail          Fail silently (no output at all) on errors (H)\n"
       " -F/--form <name=content> Specify HTTP POST data (H)\n"
       " -g/--globoff       Disable URL sequences and ranges using {} and []\n"
       " -G/--get           Send the -d data with a HTTP GET (H)");
  puts(" -h/--help          This help text\n"
       " -H/--header <line> Custom header to pass to server. (H)\n"
       " -i/--include       Include the HTTP-header in the output (H)\n"
       " -I/--head          Fetch document info only (HTTP HEAD/FTP SIZE)");
  puts(" -j/--junk-session-cookies Ignore session cookies read from file (H)\n"
       "    --interface <interface> Specify the interface to be used\n"
       "    --krb4 <level>  Enable krb4 with specified security level (F)\n"
       " -k/--insecure      Allow curl to connect to SSL sites without certs (H)\n"
       " -K/--config        Specify which config file to read\n"
       " -l/--list-only     List only names of an FTP directory (F)\n"
       "    --limit-rate <rate> Limit how fast transfers to allow");
  puts(" -L/--location      Follow Location: hints (H)\n"
       "    --location-trusted Same, and continue to send authentication when \n"
       "                    following locations, even when hostname changed\n"
       " -m/--max-time <seconds> Maximum time allowed for the transfer\n"
       " -M/--manual        Display huge help text\n"
       " -n/--netrc         Must read .netrc for user name and password\n"
       "    --netrc-optional  Use either .netrc or URL; overrides -n\n"
       " -N/--no-buffer     Disables the buffering of the output stream");
  puts(" -o/--output <file> Write output to <file> instead of stdout\n"
       " -O/--remote-name   Write output to a file named as the remote file\n"
       " -p/--proxytunnel   Perform non-HTTP services through a HTTP proxy\n"
       " -P/--ftpport <address> Use PORT with address instead of PASV when ftping (F)\n"
       " -q                 When used as the first parameter disables .curlrc\n"
       " -Q/--quote <cmd>   Send QUOTE command to FTP before file transfer (F)");
  puts(" -r/--range <range> Retrieve a byte range from a HTTP/1.1 or FTP server\n"
       " -R/--remote-time   Set the remote file's time on the local output\n"
       " -s/--silent        Silent mode. Don't output anything\n"
       " -S/--show-error    Show error. With -s, make curl show errors when they occur");
  puts("    --stderr <file> Where to redirect stderr. - means stdout.\n"
       " -t/--telnet-option <OPT=val> Set telnet option\n"
       "    --trace <file>  Dump a network/debug trace to the given file\n"
       "    --trace-ascii <file>  Like --trace but without the hex output\n"
       " -T/--upload-file <file> Transfer/upload <file> to remote site\n"
       "    --url <URL>     Another way to specify URL to work with");
  puts(" -u/--user <user[:password]> Specify user and password to use\n"
       "                    Overrides -n and --netrc-optional\n"
       " -U/--proxy-user <user[:password]> Specify Proxy authentication\n"
       " -v/--verbose       Makes the operation more talkative\n"
       " -V/--version       Outputs version number then quits");
  puts(" -w/--write-out [format] What to output after completion\n"
       " -x/--proxy <host[:port]>  Use proxy. (Default port is 1080)\n"
       "    --random-file <file> File to use for reading random data from (SSL)\n"
       " -X/--request <command> Specific request command to use");
  puts(" -y/--speed-time    Time needed to trig speed-limit abort. Defaults to 30\n"
       " -Y/--speed-limit   Stop transfer if below speed-limit for 'speed-time' secs\n"
       " -z/--time-cond <time> Includes a time condition to the server (H)\n"
       " -Z/--max-redirs <num> Set maximum number of redirections allowed (H)\n"
       " -0/--http1.0       Force usage of HTTP 1.0 (H)\n"
       " -1/--tlsv1         Force usage of TLSv1 (H)\n"
       " -2/--sslv2         Force usage of SSLv2 (H)\n"
       " -3/--sslv3         Force usage of SSLv3 (H)");
  puts(" -#/--progress-bar  Display transfer progress as a progress bar");
}

struct LongShort {
  const char *letter;
  const char *lname;
  bool extraparam;
