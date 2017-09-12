static void cliRefreshPrompt(void) {
    if (config.dbnum == 0)
        snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d> ",
            config.hostip, config.hostport);
    else
        snprintf(config.prompt,sizeof(config.prompt),"redis %s:%d[%d]> ",
            config.hostip, config.hostport, config.dbnum);
}