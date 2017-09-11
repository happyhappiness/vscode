    ldb.active = 0;
}

/* If the specified pid is among the list of children spawned for
 * forked debugging sessions, it is removed from the children list.
 * If the pid was found non-zero is returned. */
int ldbRemoveChild(pid_t pid) {
    listNode *ln = listSearchKey(ldb.children,(void*)(unsigned long)pid);
    if (ln) {
        listDelNode(ldb.children,ln);
        return 1;
    }
    return 0;
}

/* Kill all the forked sessions. */
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

/* Wrapper for EVAL / EVALSHA that enables debugging, and makes sure
 * that when EVAL returns, whatever happened, the session is ended. */
void evalGenericCommandWithDebugging(client *c, int evalsha) {
