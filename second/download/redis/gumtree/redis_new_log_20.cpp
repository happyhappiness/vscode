sds line = sdscatprintf(sdsempty(),"%s %s",option,
        value ? "yes" : "no");