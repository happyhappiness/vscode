 *--------------------------------------------------------------------------- */

/* Output command help to stdout. */
static void outputCommandHelp(struct commandHelp *help) {
    printf("\n  \x1b[1m%s\x1b[0m \x1b[90m%s\x1b[0m\n", help->name, help->params);
    printf("  \x1b[33msummary:\x1b[0m %s\n", help->summary);
    printf("  \x1b[33msince:\x1b[0m %s\n", help->since);
    printf("  \x1b[33mgroup:\x1b[0m %s\n", commandGroups[help->group]);
}

/* Return command group type by name string. */
static int commandGroupIndex(const char *name) {
    int i, len = sizeof(commandGroups)/sizeof(char*);
    for (i = 0; i < len; i++)
        if (strcasecmp(name, commandGroups[i]) == 0)
            return i;
    return -1;
}

/* Output group names. */
static void outputGroupHelp() {
    int i, len = sizeof(commandGroups)/sizeof(char*);
    for (i = 0; i < len; i++)
        printf("  \x1b[90m-\x1b[0m %s\n", commandGroups[i]);
}

/* Output all command help, filtering by group or command name. */
static void outputHelp(int argc, char **argv) {
    int i, len = sizeof(commandHelp) / sizeof(struct commandHelp);
    int group;
    struct commandHelp *help;

    if (argc && strcasecmp("groups", argv[0]) == 0) {
        outputGroupHelp();
        return;
    }

    group = argc ? commandGroupIndex(argv[0]) : -1;
    for (i = 0; i < len; i++) {
        help = &commandHelp[i];
        if (group == -1) {
            if (argc) {
                if (strcasecmp(help->name, argv[0]) == 0) {
                    outputCommandHelp(help);
                }
            } else {
                outputCommandHelp(help);
            }
        } else {
            if (group == help->group) {
                outputCommandHelp(help);
            }
        }
    }
    puts("");
}

/*------------------------------------------------------------------------------
