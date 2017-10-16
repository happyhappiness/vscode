        "    --key-type <type> Specifies private key  file type (DER/PEM/ENG) (HTTPS)\n"
        "    --pass  <pass>  Specifies passphrase for the private key (HTTPS)");
   puts("    --engine <eng>  Specifies the crypto engine to use (HTTPS)\n"
        "    --cacert <file> CA certifciate to verify peer against (SSL)\n"
        "    --capath <directory> CA directory (made using c_rehash) to verify\n"
        "                    peer against (SSL, NOT Windows)\n"
-       "    --ciphers <list> What SSL ciphers to use (SSL)");
+       "    --ciphers <list> What SSL ciphers to use (SSL)\n"
+       "    --compressed    Request a compressed response (using deflate).");
   puts("    --connect-timeout <seconds> Maximum time allowed for connection\n"
+       "    --crlf          Convert LF to CRLF in upload. Useful for MVS (OS/390)\n"
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
+       " -k/--insecure      Allow curl to connect to SSL sites without certs (H)\n"
        " -K/--config        Specify which config file to read\n"
-       " -l/--list-only     List only names of an FTP directory (F)");
+       " -l/--list-only     List only names of an FTP directory (F)\n"
+       "    --limit-rate <rate> Limit how fast transfers to allow");
   puts(" -L/--location      Follow Location: hints (H)\n"
        " -m/--max-time <seconds> Maximum time allowed for the transfer\n"
        " -M/--manual        Display huge help text\n"
        " -n/--netrc         Must read .netrc for user name and password\n"
        "    --netrc-optional  Use either .netrc or URL; overrides -n\n"
        " -N/--no-buffer     Disables the buffering of the output stream");
