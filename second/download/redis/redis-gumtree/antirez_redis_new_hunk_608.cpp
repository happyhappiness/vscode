    return NULL;
}

/* Implement the "list" command of the Lua debugger. If around is 0
 * the whole file is listed, otherwise only a small portion of the file
 * around the specified line is shown. When a line number is specified
 * the amonut of context (lines before/after) is specified via the
 * 'context' argument. */
void ldbList(int around, int context) {
    int j;

    for (j = 1; j <= ldb.lines; j++) {
        if (around != 0 && abs(around-j) > context) continue;
        char *line = ldbGetSourceLine(j);
        int mark;
        if (ldbIsBreakpoint(j))
            mark = '#';
        else
            mark = (ldb.currentline == j) ? '*' : ':';
        sds thisline = sdscatprintf(sdsempty(),"%d%c %s", j, mark, line);
        ldbLog(thisline);
    }
}

/* Read debugging commands from client. */
void ldbRepl(void) {
    sds *argv;
