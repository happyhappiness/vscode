    return arg;
}

static void usage() {
    sds version = cliVersion();
    fprintf(stderr,
"redis-cli %s\n"
