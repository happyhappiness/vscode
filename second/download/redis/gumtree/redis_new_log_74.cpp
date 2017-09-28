sds msg = sdscatprintf(sdsempty(), "%s: %d: %s",
            dbg.source, dbg.currentline, error);