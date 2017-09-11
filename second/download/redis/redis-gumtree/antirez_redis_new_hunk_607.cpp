    c->argv = argv;
    c->argc = argc;

    /* Log the command if debugging is active. */
    if (ldb.active && ldb.step) {
        sds cmdlog = sdsnew("<redis>");
        for (j = 0; j < c->argc; j++) {
            if (j == 10) {
                cmdlog = sdscatprintf(cmdlog," ... (%d more)",
                    c->argc-j-1);
            } else {
                cmdlog = sdscatlen(cmdlog," ",1);
                cmdlog = sdscatsds(cmdlog,c->argv[j]->ptr);
            }
        }
        ldbLog(cmdlog);
    }

    /* Command lookup */
    cmd = lookupCommand(argv[0]->ptr);
    if (!cmd || ((cmd->arity > 0 && cmd->arity != argc) ||
