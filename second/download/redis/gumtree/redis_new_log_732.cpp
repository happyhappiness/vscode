ldbLog(sdscatprintf(sdsempty(),"%s %s:",
                (level == 0) ? "In" : "From",
                ar.name ? ar.name : "top level"));