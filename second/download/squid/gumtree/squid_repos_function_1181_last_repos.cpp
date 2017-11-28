void
usage(void)
{
    fprintf(stderr,
            "Usage: %s [-cdzCFNRVYX] [-n name] [-s | -l facility] [-f config-file] [-[au] port] [-k signal]"
#if USE_WIN32_SERVICE
            "[-ir] [-O CommandLine]"
#endif
            "\n"
            "    -h | --help       Print help message.\n"
            "    -v | --version    Print version details.\n"
            "\n"
            "       -a port   Specify HTTP port number (default: %d).\n"
            "       -d level  Write debugging to stderr also.\n"
            "       -f file   Use given config-file instead of\n"
            "                 %s\n"
#if USE_WIN32_SERVICE
            "       -i        Installs as a Windows Service (see -n option).\n"
#endif
            "       -k reconfigure|rotate|shutdown|"
#ifdef SIGTTIN
            "restart|"
#endif
            "interrupt|kill|debug|check|parse\n"
            "                 Parse configuration file, then send signal to \n"
            "                 running copy (except -k parse) and exit.\n"
            "       -n name   Specify service name to use for service operations\n"
            "                 default is: " APP_SHORTNAME ".\n"
#if USE_WIN32_SERVICE
            "       -r        Removes a Windows Service (see -n option).\n"
#endif
            "       -s | -l facility\n"
            "                 Enable logging to syslog.\n"
            "       -u port   Specify ICP port number (default: %d), disable with 0.\n"
            "       -z        Create missing swap directories and then exit.\n"
            "       -C        Do not catch fatal signals.\n"
            "       -D        OBSOLETE. Scheduled for removal.\n"
            "       -F        Don't serve any requests until store is rebuilt.\n"
            "       -N        Master process runs in foreground and is a worker. No kids.\n"
            "       --foreground\n"
            "                 Master process runs in foreground and creates worker kids.\n"
#if USE_WIN32_SERVICE
            "       -O options\n"
            "                 Set Windows Service Command line options in Registry.\n"
#endif
            "       -R        Do not set REUSEADDR on port.\n"
            "       -S        Double-check swap during rebuild.\n"
            "       -X        Force full debugging.\n"
            "       -Y        Only return UDP_HIT or UDP_MISS_NOFETCH during fast reload.\n",
            APP_SHORTNAME, CACHE_HTTP_PORT, DefaultConfigFile, CACHE_ICP_PORT);
    exit(1);
}