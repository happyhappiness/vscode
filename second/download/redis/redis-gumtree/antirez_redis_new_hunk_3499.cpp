        return REDIS_ERR; /* avoid compiler warning */
    }

    if (output_raw_strings) {
        out = cliFormatReplyRaw(reply);
    } else {
        if (config.raw_output) {
            out = cliFormatReplyRaw(reply);
            out = sdscat(out,"\n");
        } else {
            out = cliFormatReplyTTY(reply,"");
        }
    }
    fwrite(out,sdslen(out),1,stdout);
    sdsfree(out);
    freeReplyObject(reply);
    return REDIS_OK;
}

static int cliSendCommand(int argc, char **argv, int repeat) {
    char *command = argv[0];
    size_t *argvlen;
    int j, output_raw;

    if (context == NULL) {
        printf("Not connected, please use: connect <host> <port>\n");
        return REDIS_OK;
    }

    output_raw = !strcasecmp(command,"info");
    if (!strcasecmp(command,"help") || !strcasecmp(command,"?")) {
        cliOutputHelp(--argc, ++argv);
        return REDIS_OK;
