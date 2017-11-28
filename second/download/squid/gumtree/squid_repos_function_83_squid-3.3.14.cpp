void
helpMe( void )
// purpuse: write help message and exit
{
    printf( "\nUsage:\t%s\t[-a] [-c cf] [-d l] [-(f|F) fn | -(e|E) re] "
            "[-p h[:p]]\n\t\t[-P #] [-s] [-v] [-C dir [-H]] [-n]\n\n",
            ::programname );
    printf(
        " -a\tdisplay a little rotating thingy to indicate that I am alive (tty only).\n"
        " -c c\tsquid.conf location, default \"%s\".\n"
        " -C dir\tbase directory for content extraction (copy-out mode).\n"
        " -d l\tdebug level, an OR mask of different debug options.\n"
        " -e re\tsingle regular expression per -e instance (use quotes!).\n"
        " -E re\tsingle case sensitive regular expression like -e.\n"
        " -f fn\tname of textfile containing one regular expression per line.\n"
        " -F fn\tname of textfile like -f containing case sensitive REs.\n"
        " -H\tprepend HTTP reply header to destination files in copy-out mode.\n"
        " -n\tdo not fork() when using more than one cache_dir.\n"
        " -p h:p\tcache runs on host h and optional port p, default is %s:%u.\n"
        " -P #\tif 0, just print matches; otherwise OR the following purge modes:\n"
        "\t   0x01 really send PURGE to the cache.\n"
        "\t   0x02 remove all caches files reported as 404 (not found).\n"
        "\t   0x04 remove all weird (inaccessible or too small) cache files.\n"
        "\t0 and 1 are recommended - slow rebuild your cache with other modes.\n"
        " -s\tshow all options after option parsing, but before really starting.\n"
        " -v\tshow more information about the file, e.g. MD5, timestamps and flags.\n"
        "\n", DEFAULT_SQUID_CONF, DEFAULTHOST, DEFAULTPORT );

}