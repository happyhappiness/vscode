void ldbRepl(void) {
    sds *argv;
    int argc;

    /* We continue processing commands until a command that should return
     * to the Lua interpreter is found. */
    while(1) {
        while((argv = ldbReplParseCommand(&argc)) == NULL) {
            char buf[1024];
            int nread = read(ldb.fd,buf,sizeof(buf));
            if (nread <= 0) {
                /* Make sure the script runs without user input since the
                 * client is no longer connected. */
                ldb.step = 0;
                ldb.bpcount = 0;
                return;
            }
            ldb.cbuf = sdscatlen(ldb.cbuf,buf,nread);
        }

        /* Flush the old buffer. */
        sdsfree(ldb.cbuf);
        ldb.cbuf = sdsempty();

        /* Execute the command. */
        if (!strcasecmp(argv[0],"help")) {
            ldbLog(sdsnew("Redis Lua debugger help:"));
            ldbLog(sdsnew("[s]tep     : run current line and stop again."));
            ldbLog(sdsnew("[c]continue: run till next breakpoint."));
            ldbSendLogs();
        } else if (!strcasecmp(argv[0],"s") || !strcasecmp(argv[0],"step")) {
            ldb.step = 1;
            break;
        } else if (!strcasecmp(argv[0],"c") || !strcasecmp(argv[0],"continue")){
            break;
        } else {
            ldbLog(sdsnew("Unknown Redis Lua debugger command."));
            ldbSendLogs();
        }

        /* Free the command vector. */
        sdsfreesplitres(argv,argc);
    }

    /* Free the current command argv if we break inside the while loop. */
    sdsfreesplitres(argv,argc);
}