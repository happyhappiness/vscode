    }
}

/* Set the CLI perferences. This function is invoked when an interactive
 * ":command" is called, or when reading ~/.redisclirc file, in order to
 * set user preferences. */
void cliSetPreferences(char **argv, int argc, int interactive) {
    if (!strcasecmp(argv[0],":set") && argc >= 2) {
        if (!strcasecmp(argv[1],"hints")) pref.hints = 1;
        else if (!strcasecmp(argv[1],"nohints")) pref.hints = 0;
        else {
            printf("%sunknown redis-cli preference '%s'\n",
                interactive ? "" : ".redisclirc: ",
                argv[1]);
        }
    } else {
        printf("%sunknown redis-cli internal command '%s'\n",
            interactive ? "" : ".redisclirc: ",
            argv[0]);
    }
}

/* Load the ~/.redisclirc file if any. */
void cliLoadPreferences(void) {
    sds rcfile = getDotfilePath(REDIS_CLI_RCFILE_ENV,REDIS_CLI_RCFILE_DEFAULT);
    if (rcfile == NULL) return;
    FILE *fp = fopen(rcfile,"r");
    char buf[1024];

    if (fp) {
        while(fgets(buf,sizeof(buf),fp) != NULL) {
            sds *argv;
            int argc;

            argv = sdssplitargs(buf,&argc);
            if (argc > 0) cliSetPreferences(argv,argc,0);
            sdsfreesplitres(argv,argc);
        }
    }
    sdsfree(rcfile);
}

static void repl(void) {
    sds historyfile = NULL;
    int history = 0;
