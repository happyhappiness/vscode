        " -O/--remote-name   Write output to a file named as the remote file\n"
        " -p/--proxytunnel   Perform non-HTTP services through a HTTP proxy\n"
        " -P/--ftpport <address> Use PORT with address instead of PASV when ftping (F)\n"
        " -q                 When used as the first parameter disables .curlrc\n"
        " -Q/--quote <cmd>   Send QUOTE command to FTP before file transfer (F)");
   puts(" -r/--range <range> Retrieve a byte range from a HTTP/1.1 or FTP server\n"
+       " -R/--remote-time   Set the remote file's time on the local output\n"
        " -s/--silent        Silent mode. Don't output anything\n"
        " -S/--show-error    Show error. With -s, make curl show errors when they occur\n"
        "    --stderr <file> Where to redirect stderr. - means stdout.\n"
        " -t/--telnet-option <OPT=val> Set telnet option\n"
        " -T/--upload-file <file> Transfer/upload <file> to remote site\n"
        "    --url <URL>     Another way to specify URL to work with");
