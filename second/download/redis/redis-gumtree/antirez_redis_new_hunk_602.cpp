        if (around != 0 && abs(around-j) > context) continue;
        char *line = ldbGetSourceLine(j);
        int mark;
        if (ldb.currentline == j)
            mark = '*';
        else
            mark = ldbIsBreakpoint(j) ? '#' : ':';
        sds thisline = sdscatprintf(sdsempty(),"%d%c %s", j, mark, line);
        ldbLog(thisline);
    }
