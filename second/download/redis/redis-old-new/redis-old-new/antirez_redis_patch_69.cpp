@@ -565,7 +565,7 @@ int parseOptions(int argc, const char **argv) {
 
 usage:
     printf(
-"Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n"
+"Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests>] [-k <boolean>]\n\n"
 " -h <hostname>      Server hostname (default 127.0.0.1)\n"
 " -p <port>          Server port (default 6379)\n"
 " -s <socket>        Server socket (overrides host and port)\n"