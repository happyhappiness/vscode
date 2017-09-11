    }
}

/* Return a pointer to ldb.src source code line, considering line to be
 * one-based, and returning a special string for out of range lines. */
char *ldbGetSourceLine(int line) {
    int idx = line-1;
    if (idx < 0 || idx >= ldb.lines) return "<out of range source code line>";
    return ldb.src[line];
}

/* Expect a valid multi-bulk command in the debugging client query buffer.
 * On success the command is parsed and returned as an array of SDS strings,
 * otherwise NULL is returned and there is to read more buffer. */
sds *ldbReplParseCommand(int *argcp) {
    sds *argv = NULL;
    int argc = 0;
    if (sdslen(ldb.cbuf) == 0) return NULL;

    /* Working on a copy is simpler in this case. We can modify it freely
     * for the sake of simpler parsing. */
    sds copy = sdsdup(ldb.cbuf);
    char *p = copy;

    /* This Redis protocol parser is a joke... just the simplest thing that
     * works in this context. It is also very forgiving regarding broken
     * protocol. */

    /* Seek and parse *<count>\r\n. */
    p = strchr(p,'*'); if (!p) goto protoerr;
    char *plen = p+1; /* Multi bulk len pointer. */
    p = strstr(p,"\r\n"); if (!p) goto protoerr;
    *p = '\0'; p += 2;
    *argcp = atoi(plen);
    if (*argcp <= 0 || *argcp > 1024) goto protoerr;

    /* Parse each argument. */
    argv = zmalloc(sizeof(sds)*(*argcp));
    argc = 0;
    while(argc < *argcp) {
        if (*p != '$') goto protoerr;
        plen = p+1; /* Bulk string len pointer. */
        p = strstr(p,"\r\n"); if (!p) goto protoerr;
        *p = '\0'; p += 2;
        int slen = atoi(plen); /* Length of this arg. */
        if (slen <= 0 || slen > 1024) goto protoerr;
        argv[argc++] = sdsnewlen(p,slen);
        p += slen; /* Skip the already parsed argument. */
        if (p[0] != '\r' || p[1] != '\n') goto protoerr;
        p += 2; /* Skip \r\n. */
    }
    sdsfree(copy);
    return argv;

protoerr:
    sdsfreesplitres(argv,argc);
    sdsfree(copy);
    return NULL;
}

/* Read debugging commands from client. */
void ldbRepl(void) {
    sds *argv;
    int argc;

    /* We continue processing commands until a command that should return
     * to the Lua interpreter is found. */
    while(1) {
        while((argv = ldbReplParseCommand(&argc)) == NULL) {
            char buf[1024];
            int nread = read(ldb.fd,buf,sizeof(buf));
            if (nread <= 0) {
                /* Make sure the script runs without user input since the
                 * client is no longer connected. */
                ldb.step = 0;
                ldb.bpcount = 0;
                return;
            }
            ldb.cbuf = sdscatlen(ldb.cbuf,buf,nread);
        }

        /* Flush the old buffer. */
        sdsfree(ldb.cbuf);
        ldb.cbuf = sdsempty();

        /* Execute the command. */
        if (!strcasecmp(argv[0],"help")) {
            ldbLog(sdsnew("Redis Lua debugger help:"));
            ldbLog(sdsnew("[s]tep     : run current line and stop again."));
            ldbLog(sdsnew("[c]continue: run till next breakpoint."));
            ldbSendLogs();
        } else if (!strcasecmp(argv[0],"s") || !strcasecmp(argv[0],"step")) {
            ldb.step = 1;
            break;
        } else if (!strcasecmp(argv[0],"c") || !strcasecmp(argv[0],"continue")){
            break;
        } else {
            ldbLog(sdsnew("Unknown Redis Lua debugger command."));
            ldbSendLogs();
        }

        /* Free the command vector. */
        sdsfreesplitres(argv,argc);
    }

    /* Free the current command argv if we break inside the while loop. */
    sdsfreesplitres(argv,argc);
}

/* This is the core of our Lua debugger, called each time Lua is about
 * to start executing a new line. */
void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
    lua_getstack(lua,0,ar);
    lua_getinfo(lua,"Sl",ar);
    if(strstr(ar->short_src,"user_script") == NULL) return;

    if (ldb.step) {
        ldb.step = 0;
        ldbLog(sdscatprintf(sdsempty(),"%d: %s", (int)ar->currentline,
            ldbGetSourceLine(ar->currentline-1)));
        ldbSendLogs();
        ldbRepl();
    }
}

