static void outputGroupHelp() {
    int i, len = sizeof(commandGroups)/sizeof(char*);
    for (i = 0; i < len; i++)
        printf("  \x1b[90m-\x1b[0m %s\n", commandGroups[i]);
}