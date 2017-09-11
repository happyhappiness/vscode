    return arg;
}

static void usage(void) {
    sds version = cliVersion();
    fprintf(stderr,
"redis-cli %s\n"
