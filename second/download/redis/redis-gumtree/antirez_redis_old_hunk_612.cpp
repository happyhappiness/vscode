static void cliRefreshPrompt(void) {
    int len;

    if (config.hostsocket != NULL)
        len = snprintf(config.prompt,sizeof(config.prompt),"redis %s",
                       config.hostsocket);
