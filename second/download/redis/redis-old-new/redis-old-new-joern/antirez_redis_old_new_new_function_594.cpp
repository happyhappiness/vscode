void ldbKillForkedSessions(void) {
    listIter li;
    listNode *ln;

    listRewind(ldb.children,&li);
    while((ln = listNext(&li))) {
        pid_t pid = (unsigned long) ln->value;
        serverLog(LL_WARNING,"Killing debugging session %ld",(long)pid);
        kill(pid,SIGKILL);
    }
    listRelease(ldb.children);
    ldb.children = listCreate();
}