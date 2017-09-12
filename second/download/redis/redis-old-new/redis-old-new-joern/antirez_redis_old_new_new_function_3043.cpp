static void cliRefreshPrompt(void) {
    if (config.dbnum == 0)
        snprintf(config.prompt,sizeof(config.prompt),"redis> ");
    else
        snprintf(config.prompt,sizeof(config.prompt),"redis:%d> ",config.dbnum);
}