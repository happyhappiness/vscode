    printf("\r\n");
}

#define CLI_COMPLETE_COMMAND 1
#define CLI_COMPLETE_GROUP 2

typedef struct {
    char *name;
    int type;
} completionEntry;

static completionEntry *completionEntries;
static int completionEntriesLen;

/* Build 2 different arrays for completion. One for raw command completion and one
 * for completion using HELP (including groups). */
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

static void completionCallback(const char *buf, linenoiseCompletions *lc) {
    size_t startpos = 0;
    int mask;
    int i;
    size_t matchlen;
    char *tmp;
    size_t tmpsize;

    if (strncasecmp(buf,"help ",5) == 0) {
        startpos = 5;
        while (isspace(buf[startpos])) startpos++;
        mask = CLI_COMPLETE_COMMAND | CLI_COMPLETE_GROUP;
    } else {
        mask = CLI_COMPLETE_COMMAND;
    }

    for (i = 0; i < completionEntriesLen; i++) {
        if (!(completionEntries[i].type & mask)) continue;

        matchlen = strlen(buf+startpos);
        if (strncasecmp(buf+startpos,completionEntries[i].name,matchlen) == 0) {
            tmpsize = startpos+strlen(completionEntries[i].name)+1;
            tmp = malloc(tmpsize);
            memcpy(tmp,buf,startpos);
            memcpy(tmp+startpos,completionEntries[i].name,tmpsize-startpos);
            linenoiseAddCompletion(lc,tmp);
            free(tmp);
        }
    }
}
