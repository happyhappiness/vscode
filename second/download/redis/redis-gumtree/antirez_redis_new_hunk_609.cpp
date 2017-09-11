    if(strstr(ar->short_src,"user_script") == NULL) return;

    if (ldb.step) {
        ldb.currentline = ar->currentline;
        ldb.step = 0;
        ldbLog(sdscatprintf(sdsempty(),"%d: %s", (int)ar->currentline,
            ldbGetSourceLine(ar->currentline)));
        ldbSendLogs();
        ldbRepl();
    }
