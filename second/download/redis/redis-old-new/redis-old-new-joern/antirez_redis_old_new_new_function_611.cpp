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