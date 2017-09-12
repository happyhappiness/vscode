    size_t *argvlen;
    int j;

    config.raw_output = !strcasecmp(command,"info");
    if (!strcasecmp(command,"help")) {
        showInteractiveHelp();
