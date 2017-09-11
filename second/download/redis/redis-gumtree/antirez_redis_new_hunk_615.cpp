            server.lua_kill = 1;
            addReply(c,shared.ok);
        }
    } else if (c->argc == 3 && !strcasecmp(c->argv[1]->ptr,"debug")) {
        if (clientHasPendingReplies(c)) {
            addReplyError(c,"SCRIPT DEBUG must be called outside a pipeline");
            return;
        }
        if (!strcasecmp(c->argv[2]->ptr,"no")) {
            ldbDisable(c);
        } else if (!strcasecmp(c->argv[2]->ptr,"yes")) {
            ldbEnable(c);
            addReply(c,shared.ok);
        } else if (!strcasecmp(c->argv[2]->ptr,"sync")) {
            ldbEnable(c);
            addReply(c,shared.ok);
            c->flags |= CLIENT_LUA_DEBUG_SYNC;
        } else {
            addReplyError(c,"Use SCRIPT DEBUG yes/async/no");
        }
    } else {
        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
    }
}

/* ---------------------------------------------------------------------------
 * LDB: Redis Lua debugging facilities
 * ------------------------------------------------------------------------- */

/* Initialize Lua debugger data structures. */
void ldbInit(void) {
    ldb.fd = -1;
    ldb.active = 0;
    ldb.logs = listCreate();
    ldb.traces = listCreate();
    listSetFreeMethod(ldb.logs,(void (*)(void*))sdsfree);
    listSetFreeMethod(ldb.traces, (void (*)(void*))sdsfree);
    ldb.src = NULL;
}

/* Remove all the pending messages in the specified list. */
void ldbFlushLog(list *log) {
    listNode *ln;

    while((ln = listFirst(log)) != NULL)
        listDelNode(log,ln);
}

/* Enable debug mode of Lua scripts for this client. */
void ldbEnable(client *c) {
    c->flags |= CLIENT_LUA_DEBUG;
    ldbFlushLog(ldb.logs);
    ldbFlushLog(ldb.traces);
    ldb.fd = c->fd;
    ldb.step = 0;
    ldb.bpcount = 0;
}

void ldbDisable(client *c) {
    c->flags &= ~(CLIENT_LUA_DEBUG|CLIENT_LUA_DEBUG_SYNC);
}

/* Append a log entry to the specified LDB log. */
void ldbLog(list *log, sds entry) {
    listAddNodeTail(log,entry);
}

/* Send ldb.logs and ldb.traces to the debugging client as a multi-bulk
 * reply consisting of simple strings. Log entries which include newlines
 * have them replaced with spaces. The entries sent are also consumed. */
void ldbWriteLogs(void) {
}

/* Start a debugging session before calling EVAL implementation.
 * The techique we use is to capture the client socket file descriptor,
 * in order to perform direct I/O with it from within Lua hooks. This
 * way we don't have to re-enter Redis in order to handle I/O.
 *
 * The function returns 1 if the caller should proceed to call EVAL,
 * and 0 if instead the caller should abort the operation (this happens
 * for the parent in a forked session, since it's up to the children
 * to continue, or when fork returned an error).
 *
 * The caller should call ldbEndSession() only if ldbStartSession()
 * returned 1. */
int ldbStartSession(client *c) {
    ldb.forked = (c->flags & CLIENT_LUA_DEBUG_SYNC) == 0;
    if (ldb.forked) {
        pid_t cp = fork();
        if (cp == -1) {
            addReplyError(c,"Fork() failed: can't run EVAL in debugging mode.");
            return 0;
        } else if (cp == 0) {
            /* Child */
            serverLog(LL_WARNING,"Redis forked for debugging eval");
            closeListeningSockets(0);
        } else {
            /* Parent */
            freeClientAsync(c); /* Close the client in the parent side. */
            return 0;
        }
    }

    /* Setup our debugging session. */
    anetBlock(NULL,ldb.fd);
    ldb.active = 1;
    ldb.src = c->argv[1]; /* First argument of EVAL is the script itself. */
    incrRefCount(ldb.src);
    return 1;
}

/* End a debugging session after the EVAL call with debugging enabled
 * returned. */
void ldbEndSession(client *c) {
    /* If it's a fork()ed session, we just exit. */
    if (ldb.forked) {
        writeToClient(c->fd, c, 0);
        serverLog(LL_WARNING,"Lua debugging session child exiting");
        exitFromChild(0);
    }

    /* Otherwise let's restore client's state. */
    anetNonBlock(NULL,ldb.fd);
    ldb.active = 0;
    decrRefCount(ldb.src);
}

/* Wrapper for EVAL / EVALSHA that enables debugging, and makes sure
 * that when EVAL returns, whatever happened, the session is ended. */
void evalGenericCommandWithDebugging(client *c, int evalsha) {
    if (ldbStartSession(c)) {
        evalGenericCommand(c,evalsha);
        ldbEndSession(c);
    } else {
        ldbDisable(c);
    }
}

/* This is the core of our Lua debugger, called each time Lua is about
 * to start executing a new line. */
void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
    lua_getstack(lua,0,ar);
    lua_getinfo(lua,"Sl",ar);
    if(strstr(ar->short_src,"user_script") != NULL)
        printf("%s %d\n", ar->short_src, (int) ar->currentline);
}



