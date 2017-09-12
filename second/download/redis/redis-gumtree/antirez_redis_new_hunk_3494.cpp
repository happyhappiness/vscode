}

static void usage() {
    sds version = cliVersion();
    fprintf(stderr,
"redis-cli %s\n"
"\n"
"Usage: redis-cli [OPTIONS] [cmd [arg [arg ...]]]\n"
"  -h <hostname>    Server hostname (default: 127.0.0.1)\n"
"  -p <port>        Server port (default: 6379)\n"
"  -s <socket>      Server socket (overrides hostname and port)\n"
"  -a <password>    Password to use when connecting to the server\n"
"  -r <repeat>      Execute specified command N times\n"
"  -n <db>          Database number\n"
"  -x               Read last argument from STDIN\n"
"  -d <delimiter>   Multi-bulk delimiter in for raw formatting (default: \\n)\n"
"  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
"  --help           Output this help and exit\n"
"  --version        Output version and exit\n"
"\n"
"Examples:\n"
"  cat /etc/passwd | redis-cli -x set mypasswd\n"
"  redis-cli get mypasswd\n"
"  redis-cli -r 100 lpush mylist x\n"
"\n"
"When no command is given, redis-cli starts in interactive mode.\n"
"Type \"help\" in interactive mode for information on available commands.\n"
"\n",
        version);
    sdsfree(version);
    exit(1);
}

