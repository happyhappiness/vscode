    return retval;
}

static int evalMode(int argc, char **argv) {
    sds script = sdsempty();
    FILE *fp;
    char buf[1024];
    size_t nread;
    char **argv2;
    int j, got_comma = 0, keys = 0;

    /* Load the script from the file, as an sds string. */
    fp = fopen(config.eval,"r");
    if (!fp) {
        fprintf(stderr,
            "Can't open file '%s': %s\n", config.eval, strerror(errno));
        exit(1);
    }
    while((nread = fread(buf,1,sizeof(buf),fp)) != 0) {
        script = sdscatlen(script,buf,nread);
    }
    fclose(fp);

    /* Create our argument vector */
    argv2 = zmalloc(sizeof(sds)*(argc+3));
    argv2[0] = sdsnew("EVAL");
    argv2[1] = script;
    for (j = 0; j < argc; j++) {
        if (!got_comma && argv[j][0] == ',' && argv[j][1] == 0) {
            got_comma = 1;
            continue;
        }
        argv2[j+3-got_comma] = sdsnew(argv[j]);
        if (!got_comma) keys++;
    }
    argv2[2] = sdscatprintf(sdsempty(),"%d",keys);

    /* Call it */
    return cliSendCommand(argc+3-got_comma, argv2, config.repeat);
}

static void latencyMode(void) {
    redisReply *reply;
    long long start, latency, min, max, tot, count = 0;
