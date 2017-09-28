 usage:
     printf(
 "Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n"
 " -h <hostname>      Server hostname (default 127.0.0.1)\n"
 " -p <port>          Server port (default 6379)\n"
 " -s <socket>        Server socket (overrides host and port)\n"
+" -a <password>      Password for Redis Auth\n"
 " -c <clients>       Number of parallel connections (default 50)\n"
 " -n <requests>      Total number of requests (default 10000)\n"
 " -d <size>          Data size of SET/GET value in bytes (default 2)\n"
 " -dbnum <db>        SELECT the specified db number (default 0)\n"
 " -k <boolean>       1=keep alive 0=reconnect (default 1)\n"
 " -r <keyspacelen>   Use random keys for SET/GET/INCR, random values for SADD\n"
