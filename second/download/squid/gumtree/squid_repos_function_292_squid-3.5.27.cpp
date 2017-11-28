static void readConfig(const char *filename)
{
    char line[TQ_BUFFERSIZE];        /* the buffer for the lines read
                   from the dict file */
    char *cp;           /* a char pointer used to parse
                   each line */
    char *username;     /* for the username */
    char *budget;
    char *period;
    FILE *FH;
    time_t t;
    time_t budgetSecs, periodSecs;
    time_t start;

    log_info("reading config file \"%s\".\n", filename);

    FH = fopen(filename, "r");
    if ( FH ) {
        /* the pointer to the first entry in the linked list */
        unsigned int lineCount = 0;
        while (fgets(line, sizeof(line), FH)) {
            ++lineCount;
            if (line[0] == '#') {
                continue;
            }
            if ((cp = strchr (line, '\n')) != NULL) {
                /* chop \n characters */
                *cp = '\0';
            }
            log_debug("read config line %u: \"%s\".\n", lineCount, line);
            if ((username = strtok(line, "\t ")) != NULL) {

                /* get the time budget */
                if ((budget = strtok(NULL, "/")) == NULL) {
                    fprintf(stderr, "ERROR: missing 'budget' field on line %u of '%s'.\n", lineCount, filename);
                    continue;
                }
                if ((period = strtok(NULL, "/")) == NULL) {
                    fprintf(stderr, "ERROR: missing 'period' field on line %u of '%s'.\n", lineCount, filename);
                    continue;
                }

                parseTime(budget, &budgetSecs, &start);
                parseTime(period, &periodSecs, &start);

                log_debug("read time quota for user \"%s\": %lds / %lds starting %lds\n",
                          username, budgetSecs, periodSecs, start);

                writeTime(username, KEY_PERIOD_START, start);
                writeTime(username, KEY_PERIOD_LENGTH_CONFIGURED, periodSecs);
                writeTime(username, KEY_TIME_BUDGET_CONFIGURED, budgetSecs);
                t = readTime(username, KEY_TIME_BUDGET_CONFIGURED);
                writeTime(username, KEY_TIME_BUDGET_LEFT, t);
            }
        }
        fclose(FH);
    } else {
        perror(filename);
    }
}