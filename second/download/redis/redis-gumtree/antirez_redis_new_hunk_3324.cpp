
#define LINE_BUFLEN 4096
static void repl() {
    sds historyfile = NULL;
    int history = 0;
    char *line;
    int argc;
    sds *argv;

    config.interactive = 1;
    linenoiseSetCompletionCallback(completionCallback);

    /* Only use history when stdin is a tty. */
    if (isatty(fileno(stdin))) {
        history = 1;

        if (getenv("HOME") != NULL) {
            historyfile = sdscatprintf(sdsempty(),"%s/.rediscli_history",getenv("HOME"));
            linenoiseHistoryLoad(historyfile);
        }
    }

    while((line = linenoise(context ? "redis> " : "not connected> ")) != NULL) {
        if (line[0] != '\0') {
            argv = sdssplitargs(line,&argc);
            if (history) linenoiseHistoryAdd(line);
            if (historyfile) linenoiseHistorySave(historyfile);

            if (argv == NULL) {
                printf("Invalid argument(s)\n");
                continue;
