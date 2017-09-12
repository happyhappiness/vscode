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

    /* If we are debugging a script, enable the Lua debugger. */
    if (config.eval_ldb) {
        redisReply *reply = redisCommand(context,
                config.eval_ldb_sync ? "SCRIPT DEBUG sync": "SCRIPT DEBUG yes");
        if (reply) freeReplyObject(reply);
    }

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
    int eval_ldb = config.eval_ldb; /* Save it, may be reverteed. */
    int retval = issueCommand(argc+3-got_comma, argv2);
    if (eval_ldb) {
        if (!config.eval_ldb) {
            /* If the debugging session ended immediately, there was an
             * error compiling the script. Show it and don't enter
             * the REPL at all. */
            printf("Eval debugging session can't start:\n");
            cliReadReply(0);
        } else {
            strncpy(config.prompt,"lua debugger> ",sizeof(config.prompt));
            repl();
        }
    }
    return retval;
}