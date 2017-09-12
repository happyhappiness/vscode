    size_t *argvlen;
    int j;

    if (context == NULL) {
        printf("Not connected, please use: connect <host> <port>\n");
        return REDIS_OK;
    }

    config.raw_output = !strcasecmp(command,"info");
    if (!strcasecmp(command,"help")) {
        showInteractiveHelp();
