    size_t *argvlen;
    int j, output_raw;

    if (context == NULL) {
        printf("Not connected, please use: connect <host> <port>\n");
        return REDIS_OK;
    }

    output_raw = 0;
    if (!strcasecmp(command,"info") ||
