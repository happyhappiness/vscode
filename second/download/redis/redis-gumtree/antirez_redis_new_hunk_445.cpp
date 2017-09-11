    helpEntry tmp;

    helpEntriesLen = len = commandslen+groupslen;
    helpEntries = zmalloc(sizeof(helpEntry)*len);

    for (i = 0; i < groupslen; i++) {
        tmp.argc = 1;
        tmp.argv = zmalloc(sizeof(sds));
        tmp.argv[0] = sdscatprintf(sdsempty(),"@%s",commandGroups[i]);
        tmp.full = tmp.argv[0];
        tmp.type = CLI_HELP_GROUP;
