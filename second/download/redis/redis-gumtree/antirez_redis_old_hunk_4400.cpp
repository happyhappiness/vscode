    }
}

static struct redisCommand *lookupCommand(char *name) {
    int j = 0;
    while(cmdTable[j].name != NULL) {
