static void usage() {
    sds version = cliVersion();
    fprintf(stderr,
"redis-cli %s\n"
"\n"
"Usage: redis-cli [OPTIONS] [cmd [arg [arg ...]]]\n"
"  -h <hostname>      Server hostname (default: 127.0.0.1)\n"
"  -p <port>          Server port (default: 6379)\n"
"  -s <socket>        Server socket (overrides hostname and port)\n"
"  -a <password>      Password to use when connecting to the server\n"
"  -r <repeat>        Execute specified command N times\n"
"  -i <interval>      When -r is used, waits <interval> seconds per command.\n"
"                     It is possible to specify sub-second times like -i 0.1\n"
"  -n <db>            Database number\n"
"  -x                 Read last argument from STDIN\n"
"  -d <delimiter>     Multi-bulk delimiter in for raw formatting (default: \\n)\n"
"  -c                 Enable cluster mode (follow -ASK and -MOVED redirections)\n"
"  --raw              Use raw formatting for replies (default when STDOUT is\n"
"                     not a tty)\n"
"  --csv              Output in CSV format\n"
"  --latency          Enter a special mode continuously sampling latency\n"
"  --latency-history  Like --latency but tracking latency changes over time.\n"
"                     Default time interval is 15 sec. Change it using -i.\n"
"  --slave            Simulate a slave showing commands received from the master\n"
"  --rdb <filename>   Transfer an RDB dump from remote server to local file.\n"
"  --pipe             Transfer raw Redis protocol from stdin to server\n"
"  --pipe-timeout <n> In --pipe mode, abort with error if after sending all data\n"
"                     no reply is received within <n> seconds.\n"
"                     Default timeout: %d. Use 0 to wait forever.\n"
"  --bigkeys          Sample Redis keys looking for big keys\n"
"  --eval <file>      Send an EVAL command using the Lua script at <file>\n"
"  --help             Output this help and exit\n"
"  --version          Output version and exit\n"
"\n"
"Examples:\n"
"  cat /etc/passwd | redis-cli -x set mypasswd\n"
"  redis-cli get mypasswd\n"
"  redis-cli -r 100 lpush mylist x\n"
"  redis-cli -r 100 -i 1 info | grep used_memory_human:\n"
"  redis-cli --eval myscript.lua key1 key2 , arg1 arg2 arg3\n"
"  (Note: when using --eval the comma separates KEYS[] from ARGV[] items)\n"
"\n"
"When no command is given, redis-cli starts in interactive mode.\n"
"Type \"help\" in interactive mode for information on available commands.\n"
"\n",
        version, REDIS_DEFAULT_PIPE_TIMEOUT);
    sdsfree(version);
    exit(1);
}

/* Turn the plain C strings into Sds strings */
static char **convertToSds(int count, char** args) {
