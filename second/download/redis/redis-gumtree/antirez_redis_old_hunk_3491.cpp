        return REDIS_ERR; /* avoid compiler warning */
    }

    out = cliFormatReply(reply,"");
    freeReplyObject(reply);
    fwrite(out,sdslen(out),1,stdout);
    sdsfree(out);
    return REDIS_OK;
}

static int cliSendCommand(int argc, char **argv, int repeat) {
    char *command = argv[0];
    size_t *argvlen;
    int j;

    if (context == NULL) {
        printf("Not connected, please use: connect <host> <port>\n");
        return REDIS_OK;
    }

    config.raw_output = !strcasecmp(command,"info");
    if (!strcasecmp(command,"help") || !strcasecmp(command,"?")) {
        cliOutputHelp(--argc, ++argv);
        return REDIS_OK;
