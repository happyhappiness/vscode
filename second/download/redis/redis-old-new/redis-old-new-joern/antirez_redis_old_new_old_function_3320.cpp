static void cliInitHelp() {
    int commandslen = sizeof(commandHelp)/sizeof(struct commandHelp);
    int groupslen = sizeof(commandGroups)/sizeof(char*);
    int i, len, pos = 0;
    completionEntry tmp;

    completionEntriesLen = len = commandslen+groupslen;
    completionEntries = malloc(sizeof(completionEntry)*len);

    for (i = 0; i < groupslen; i++) {
        tmp.name = malloc(strlen(commandGroups[i]+2));
        sprintf(tmp.name,"@%s",commandGroups[i]);
        tmp.type = CLI_COMPLETE_GROUP;
        completionEntries[pos++] = tmp;
    }

    for (i = 0; i < commandslen; i++) {
        tmp.name = commandHelp[i].name;
        tmp.type = CLI_COMPLETE_COMMAND;
        completionEntries[pos++] = tmp;
    }
}