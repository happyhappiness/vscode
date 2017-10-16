        "    --key <key>     Specifies private key file (HTTPS)\n"
        "    --key-type <type> Specifies private key  file type (DER/PEM/ENG) (HTTPS)\n"
        "    --pass  <pass>  Specifies passphrase for the private key (HTTPS)");
   puts("    --engine <eng>  Specifies the crypto engine to use (HTTPS)\n"
        "    --cacert <file> CA certifciate to verify peer against (SSL)\n"
        "    --capath <directory> CA directory (made using c_rehash) to verify\n"
-       "                    peer against (SSL, NOT Windows)\n"
+       "                    peer against (SSL)\n"
        "    --ciphers <list> What SSL ciphers to use (SSL)\n"
        "    --compressed    Request a compressed response (using deflate).");
   puts("    --connect-timeout <seconds> Maximum time allowed for connection\n"
+       "    --create-dirs   Create the necessary local directory hierarchy\n"
        "    --crlf          Convert LF to CRLF in upload. Useful for MVS (OS/390)\n"
        " -f/--fail          Fail silently (no output at all) on errors (H)\n"
        " -F/--form <name=content> Specify HTTP POST data (H)\n"
        " -g/--globoff       Disable URL sequences and ranges using {} and []\n"
        " -G/--get           Send the -d data with a HTTP GET (H)");
   puts(" -h/--help          This help text\n"
