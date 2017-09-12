
#define LINE_BUFLEN 4096
static void repl() {
    int argc, j;
    char *line;
    sds *argv;

    config.interactive = 1;
    linenoiseSetCompletionCallback(completionCallback);

    while((line = linenoise(context ? "redis> " : "not connected> ")) != NULL) {
        if (line[0] != '\0') {
            argv = sdssplitargs(line,&argc);
            linenoiseHistoryAdd(line);
            if (config.historyfile) linenoiseHistorySave(config.historyfile);
            if (argv == NULL) {
                printf("Invalid argument(s)\n");
                continue;
