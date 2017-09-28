         funcname[0] = 'f';
         funcname[1] = '_';
         sha1hex(funcname+2,c->argv[2]->ptr,sdslen(c->argv[2]->ptr));
         sha = sdsnewlen(funcname+2,40);
         if (dictFind(server.lua_scripts,sha) == NULL) {
             if (luaCreateFunction(c,server.lua,funcname,c->argv[2])
-                    == REDIS_ERR) {
+                    == C_ERR) {
                 sdsfree(sha);
                 return;
             }
         }
         addReplyBulkCBuffer(c,funcname+2,40);
         sdsfree(sha);
-        forceCommandPropagation(c,REDIS_PROPAGATE_REPL|REDIS_PROPAGATE_AOF);
+        forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
     } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"kill")) {
         if (server.lua_caller == NULL) {
             addReplySds(c,sdsnew("-NOTBUSY No scripts in execution right now.\r\n"));
         } else if (server.lua_write_dirty) {
             addReplySds(c,sdsnew("-UNKILLABLE Sorry the script already executed write commands against the dataset. You can either wait the script termination or kill the server in a hard way using the SHUTDOWN NOSAVE command.\r\n"));
         } else {
             server.lua_kill = 1;
             addReply(c,shared.ok);
         }
+    } else if (c->argc == 3 && !strcasecmp(c->argv[1]->ptr,"debug")) {
+        if (clientHasPendingReplies(c)) {
+            addReplyError(c,"SCRIPT DEBUG must be called outside a pipeline");
+            return;
+        }
+        if (!strcasecmp(c->argv[2]->ptr,"no")) {
+            ldbDisable(c);
+            addReply(c,shared.ok);
+        } else if (!strcasecmp(c->argv[2]->ptr,"yes")) {
+            ldbEnable(c);
+            addReply(c,shared.ok);
+        } else if (!strcasecmp(c->argv[2]->ptr,"sync")) {
+            ldbEnable(c);
+            addReply(c,shared.ok);
+            c->flags |= CLIENT_LUA_DEBUG_SYNC;
+        } else {
+            addReplyError(c,"Use SCRIPT DEBUG yes/sync/no");
+        }
     } else {
         addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
     }
 }
+
+/* ---------------------------------------------------------------------------
+ * LDB: Redis Lua debugging facilities
+ * ------------------------------------------------------------------------- */
+
+/* Initialize Lua debugger data structures. */
+void ldbInit(void) {
+    ldb.fd = -1;
+    ldb.active = 0;
+    ldb.logs = listCreate();
+    listSetFreeMethod(ldb.logs,(void (*)(void*))sdsfree);
+    ldb.children = listCreate();
+    ldb.src = NULL;
+    ldb.lines = 0;
+    ldb.cbuf = sdsempty();
+}
+
+/* Remove all the pending messages in the specified list. */
+void ldbFlushLog(list *log) {
+    listNode *ln;
+
+    while((ln = listFirst(log)) != NULL)
+        listDelNode(log,ln);
+}
+
+/* Enable debug mode of Lua scripts for this client. */
+void ldbEnable(client *c) {
+    c->flags |= CLIENT_LUA_DEBUG;
+    ldbFlushLog(ldb.logs);
+    ldb.fd = c->fd;
+    ldb.step = 1;
+    ldb.bpcount = 0;
+    ldb.luabp = 0;
+    sdsfree(ldb.cbuf);
+    ldb.cbuf = sdsempty();
+    ldb.maxlen = LDB_MAX_LEN_DEFAULT;
+    ldb.maxlen_hint_sent = 0;
+}
+
+/* Exit debugging mode from the POV of client. This function is not enough
+ * to properly shut down a client debugging session, see ldbEndSession()
+ * for more information. */
+void ldbDisable(client *c) {
+    c->flags &= ~(CLIENT_LUA_DEBUG|CLIENT_LUA_DEBUG_SYNC);
+}
+
+/* Append a log entry to the specified LDB log. */
+void ldbLog(sds entry) {
+    listAddNodeTail(ldb.logs,entry);
+}
+
+/* A version of ldbLog() which prevents producing logs greater than
+ * ldb.maxlen. The first time the limit is reached an hint is generated
+ * to inform the user that reply trimming can be disabled using the
+ * debugger "maxlen" command. */
+void ldbLogWithMaxLen(sds entry) {
+    int trimmed = 0;
+    if (ldb.maxlen && sdslen(entry) > ldb.maxlen) {
+        sdsrange(entry,0,ldb.maxlen-1);
+        entry = sdscatlen(entry," ...",4);
+        trimmed = 1;
+    }
+    ldbLog(entry);
+    if (trimmed && ldb.maxlen_hint_sent == 0) {
+        ldb.maxlen_hint_sent = 1;
+        ldbLog(sdsnew(
+        "<hint> The above reply was trimmed. Use 'maxlen 0' to disable trimming."));
+    }
+}
+
+/* Send ldb.logs to the debugging client as a multi-bulk reply
+ * consisting of simple strings. Log entries which include newlines have them
+ * replaced with spaces. The entries sent are also consumed. */
+void ldbSendLogs(void) {
+    sds proto = sdsempty();
+    proto = sdscatfmt(proto,"*%i\r\n", (int)listLength(ldb.logs));
+    while(listLength(ldb.logs)) {
+        listNode *ln = listFirst(ldb.logs);
+        proto = sdscatlen(proto,"+",1);
+        sdsmapchars(ln->value,"\r\n","  ",2);
+        proto = sdscatsds(proto,ln->value);
+        proto = sdscatlen(proto,"\r\n",2);
+        listDelNode(ldb.logs,ln);
+    }
+    if (write(ldb.fd,proto,sdslen(proto)) == -1) {
+        /* Avoid warning. We don't check the return value of write()
+         * since the next read() will catch the I/O error and will
+         * close the debugging session. */
+    }
+    sdsfree(proto);
+}
+
+/* Start a debugging session before calling EVAL implementation.
+ * The techique we use is to capture the client socket file descriptor,
+ * in order to perform direct I/O with it from within Lua hooks. This
+ * way we don't have to re-enter Redis in order to handle I/O.
+ *
+ * The function returns 1 if the caller should proceed to call EVAL,
+ * and 0 if instead the caller should abort the operation (this happens
+ * for the parent in a forked session, since it's up to the children
+ * to continue, or when fork returned an error).
+ *
+ * The caller should call ldbEndSession() only if ldbStartSession()
+ * returned 1. */
+int ldbStartSession(client *c) {
+    ldb.forked = (c->flags & CLIENT_LUA_DEBUG_SYNC) == 0;
+    if (ldb.forked) {
+        pid_t cp = fork();
+        if (cp == -1) {
+            addReplyError(c,"Fork() failed: can't run EVAL in debugging mode.");
+            return 0;
+        } else if (cp == 0) {
+            /* Child. Let's ignore important signals handled by the parent. */
+            struct sigaction act;
+            sigemptyset(&act.sa_mask);
+            act.sa_flags = 0;
+            act.sa_handler = SIG_IGN;
+            sigaction(SIGTERM, &act, NULL);
+            sigaction(SIGINT, &act, NULL);
+
+            /* Log the creation of the child and close the listening
+             * socket to make sure if the parent crashes a reset is sent
+             * to the clients. */
+            serverLog(LL_WARNING,"Redis forked for debugging eval");
+            closeListeningSockets(0);
+        } else {
+            /* Parent */
+            listAddNodeTail(ldb.children,(void*)(unsigned long)cp);
+            freeClientAsync(c); /* Close the client in the parent side. */
+            return 0;
+        }
+    } else {
+        serverLog(LL_WARNING,
+            "Redis synchronous debugging eval session started");
+    }
+
+    /* Setup our debugging session. */
+    anetBlock(NULL,ldb.fd);
+    anetSendTimeout(NULL,ldb.fd,5000);
+    ldb.active = 1;
+
+    /* First argument of EVAL is the script itself. We split it into different
+     * lines since this is the way the debugger accesses the source code. */
+    sds srcstring = sdsdup(c->argv[1]->ptr);
+    size_t srclen = sdslen(srcstring);
+    while(srclen && (srcstring[srclen-1] == '\n' ||
+                     srcstring[srclen-1] == '\r'))
+    {
+        srcstring[--srclen] = '\0';
+    }
+    sdssetlen(srcstring,srclen);
+    ldb.src = sdssplitlen(srcstring,sdslen(srcstring),"\n",1,&ldb.lines);
+    sdsfree(srcstring);
+    return 1;
+}
+
+/* End a debugging session after the EVAL call with debugging enabled
+ * returned. */
+void ldbEndSession(client *c) {
+    /* Emit the remaining logs and an <endsession> mark. */
+    ldbLog(sdsnew("<endsession>"));
+    ldbSendLogs();
+
+    /* If it's a fork()ed session, we just exit. */
+    if (ldb.forked) {
+        writeToClient(c->fd, c, 0);
+        serverLog(LL_WARNING,"Lua debugging session child exiting");
+        exitFromChild(0);
+    } else {
+        serverLog(LL_WARNING,
+            "Redis synchronous debugging eval session ended");
+    }
+
+    /* Otherwise let's restore client's state. */
+    anetNonBlock(NULL,ldb.fd);
+    anetSendTimeout(NULL,ldb.fd,0);
+
+    /* Close the client connectin after sending the final EVAL reply
+     * in order to signal the end of the debugging session. */
+    c->flags |= CLIENT_CLOSE_AFTER_REPLY;
+
+    /* Cleanup. */
+    sdsfreesplitres(ldb.src,ldb.lines);
+    ldb.lines = 0;
+    ldb.active = 0;
+}
+
+/* If the specified pid is among the list of children spawned for
+ * forked debugging sessions, it is removed from the children list.
+ * If the pid was found non-zero is returned. */
+int ldbRemoveChild(pid_t pid) {
+    listNode *ln = listSearchKey(ldb.children,(void*)(unsigned long)pid);
+    if (ln) {
+        listDelNode(ldb.children,ln);
+        return 1;
+    }
+    return 0;
+}
+
+/* Return the number of children we still did not received termination
+ * acknowledge via wait() in the parent process. */
+int ldbPendingChildren(void) {
+    return listLength(ldb.children);
+}
+
+/* Kill all the forked sessions. */
+void ldbKillForkedSessions(void) {
+    listIter li;
+    listNode *ln;
+
+    listRewind(ldb.children,&li);
+    while((ln = listNext(&li))) {
+        pid_t pid = (unsigned long) ln->value;
+        serverLog(LL_WARNING,"Killing debugging session %ld",(long)pid);
+        kill(pid,SIGKILL);
+    }
+    listRelease(ldb.children);
+    ldb.children = listCreate();
+}
+
+/* Wrapper for EVAL / EVALSHA that enables debugging, and makes sure
+ * that when EVAL returns, whatever happened, the session is ended. */
+void evalGenericCommandWithDebugging(client *c, int evalsha) {
+    if (ldbStartSession(c)) {
+        evalGenericCommand(c,evalsha);
+        ldbEndSession(c);
+    } else {
+        ldbDisable(c);
+    }
+}
+
+/* Return a pointer to ldb.src source code line, considering line to be
+ * one-based, and returning a special string for out of range lines. */
+char *ldbGetSourceLine(int line) {
+    int idx = line-1;
+    if (idx < 0 || idx >= ldb.lines) return "<out of range source code line>";
+    return ldb.src[idx];
+}
+
+/* Return true if there is a breakpoint in the specified line. */
+int ldbIsBreakpoint(int line) {
+    int j;
+
+    for (j = 0; j < ldb.bpcount; j++)
+        if (ldb.bp[j] == line) return 1;
+    return 0;
+}
+
+/* Add the specified breakpoint. Ignore it if we already reached the max.
+ * Returns 1 if the breakpoint was added (or was already set). 0 if there is
+ * no space for the breakpoint or if the line is invalid. */
+int ldbAddBreakpoint(int line) {
+    if (line <= 0 || line > ldb.lines) return 0;
+    if (!ldbIsBreakpoint(line) && ldb.bpcount != LDB_BREAKPOINTS_MAX) {
+        ldb.bp[ldb.bpcount++] = line;
+        return 1;
+    }
+    return 0;
+}
+
+/* Remove the specified breakpoint, returning 1 if the operation was
+ * performed or 0 if there was no such breakpoint. */
+int ldbDelBreakpoint(int line) {
+    int j;
+
+    for (j = 0; j < ldb.bpcount; j++) {
+        if (ldb.bp[j] == line) {
+            ldb.bpcount--;
+            memmove(ldb.bp+j,ldb.bp+j+1,ldb.bpcount-j);
+            return 1;
+        }
+    }
+    return 0;
+}
+
+/* Expect a valid multi-bulk command in the debugging client query buffer.
+ * On success the command is parsed and returned as an array of SDS strings,
+ * otherwise NULL is returned and there is to read more buffer. */
+sds *ldbReplParseCommand(int *argcp) {
+    sds *argv = NULL;
+    int argc = 0;
+    if (sdslen(ldb.cbuf) == 0) return NULL;
+
+    /* Working on a copy is simpler in this case. We can modify it freely
+     * for the sake of simpler parsing. */
+    sds copy = sdsdup(ldb.cbuf);
+    char *p = copy;
+
+    /* This Redis protocol parser is a joke... just the simplest thing that
+     * works in this context. It is also very forgiving regarding broken
+     * protocol. */
+
+    /* Seek and parse *<count>\r\n. */
+    p = strchr(p,'*'); if (!p) goto protoerr;
+    char *plen = p+1; /* Multi bulk len pointer. */
+    p = strstr(p,"\r\n"); if (!p) goto protoerr;
+    *p = '\0'; p += 2;
+    *argcp = atoi(plen);
+    if (*argcp <= 0 || *argcp > 1024) goto protoerr;
+
+    /* Parse each argument. */
+    argv = zmalloc(sizeof(sds)*(*argcp));
+    argc = 0;
+    while(argc < *argcp) {
+        if (*p != '$') goto protoerr;
+        plen = p+1; /* Bulk string len pointer. */
+        p = strstr(p,"\r\n"); if (!p) goto protoerr;
+        *p = '\0'; p += 2;
+        int slen = atoi(plen); /* Length of this arg. */
+        if (slen <= 0 || slen > 1024) goto protoerr;
+        argv[argc++] = sdsnewlen(p,slen);
+        p += slen; /* Skip the already parsed argument. */
+        if (p[0] != '\r' || p[1] != '\n') goto protoerr;
+        p += 2; /* Skip \r\n. */
+    }
+    sdsfree(copy);
+    return argv;
+
+protoerr:
+    sdsfreesplitres(argv,argc);
+    sdsfree(copy);
+    return NULL;
+}
+
+/* Log the specified line in the Lua debugger output. */
+void ldbLogSourceLine(int lnum) {
+    char *line = ldbGetSourceLine(lnum);
+    char *prefix;
+    int bp = ldbIsBreakpoint(lnum);
+    int current = ldb.currentline == lnum;
+
+    if (current && bp)
+        prefix = "->#";
+    else if (current)
+        prefix = "-> ";
+    else if (bp)
+        prefix = "  #";
+    else
+        prefix = "   ";
+    sds thisline = sdscatprintf(sdsempty(),"%s%-3d %s", prefix, lnum, line);
+    ldbLog(thisline);
+}
+
+/* Implement the "list" command of the Lua debugger. If around is 0
+ * the whole file is listed, otherwise only a small portion of the file
+ * around the specified line is shown. When a line number is specified
+ * the amonut of context (lines before/after) is specified via the
+ * 'context' argument. */
+void ldbList(int around, int context) {
+    int j;
+
+    for (j = 1; j <= ldb.lines; j++) {
+        if (around != 0 && abs(around-j) > context) continue;
+        ldbLogSourceLine(j);
+    }
+}
+
+/* Append an human readable representation of the Lua value at position 'idx'
+ * on the stack of the 'lua' state, to the SDS string passed as argument.
+ * The new SDS string with the represented value attached is returned.
+ * Used in order to implement ldbLogStackValue().
+ *
+ * The element is not automatically removed from the stack, nor it is
+ * converted to a different type. */
+#define LDB_MAX_VALUES_DEPTH (LUA_MINSTACK/2)
+sds ldbCatStackValueRec(sds s, lua_State *lua, int idx, int level) {
+    int t = lua_type(lua,idx);
+
+    if (level++ == LDB_MAX_VALUES_DEPTH)
+        return sdscat(s,"<max recursion level reached! Nested table?>");
+
+    switch(t) {
+    case LUA_TSTRING:
+        {
+        size_t strl;
+        char *strp = (char*)lua_tolstring(lua,idx,&strl);
+        s = sdscatrepr(s,strp,strl);
+        }
+        break;
+    case LUA_TBOOLEAN:
+        s = sdscat(s,lua_toboolean(lua,idx) ? "true" : "false");
+        break;
+    case LUA_TNUMBER:
+        s = sdscatprintf(s,"%g",(double)lua_tonumber(lua,idx));
+        break;
+    case LUA_TNIL:
+        s = sdscatlen(s,"nil",3);
+        break;
+    case LUA_TTABLE:
+        {
+        int expected_index = 1; /* First index we expect in an array. */
+        int is_array = 1; /* Will be set to null if check fails. */
+        /* Note: we create two representations at the same time, one
+         * assuming the table is an array, one assuming it is not. At the
+         * end we know what is true and select the right one. */
+        sds repr1 = sdsempty();
+        sds repr2 = sdsempty();
+        lua_pushnil(lua); /* The first key to start the iteration is nil. */
+        while (lua_next(lua,idx-1)) {
+            /* Test if so far the table looks like an array. */
+            if (is_array &&
+                (lua_type(lua,-2) != LUA_TNUMBER ||
+                 lua_tonumber(lua,-2) != expected_index)) is_array = 0;
+            /* Stack now: table, key, value */
+            /* Array repr. */
+            repr1 = ldbCatStackValueRec(repr1,lua,-1,level);
+            repr1 = sdscatlen(repr1,"; ",2);
+            /* Full repr. */
+            repr2 = sdscatlen(repr2,"[",1);
+            repr2 = ldbCatStackValueRec(repr2,lua,-2,level);
+            repr2 = sdscatlen(repr2,"]=",2);
+            repr2 = ldbCatStackValueRec(repr2,lua,-1,level);
+            repr2 = sdscatlen(repr2,"; ",2);
+            lua_pop(lua,1); /* Stack: table, key. Ready for next iteration. */
+            expected_index++;
+        }
+        /* Strip the last " ;" from both the representations. */
+        if (sdslen(repr1)) sdsrange(repr1,0,-3);
+        if (sdslen(repr2)) sdsrange(repr2,0,-3);
+        /* Select the right one and discard the other. */
+        s = sdscatlen(s,"{",1);
+        s = sdscatsds(s,is_array ? repr1 : repr2);
+        s = sdscatlen(s,"}",1);
+        sdsfree(repr1);
+        sdsfree(repr2);
+        }
+        break;
+    case LUA_TFUNCTION:
+    case LUA_TUSERDATA:
+    case LUA_TTHREAD:
+    case LUA_TLIGHTUSERDATA:
+        {
+        const void *p = lua_topointer(lua,idx);
+        char *typename = "unknown";
+        if (t == LUA_TFUNCTION) typename = "function";
+        else if (t == LUA_TUSERDATA) typename = "userdata";
+        else if (t == LUA_TTHREAD) typename = "thread";
+        else if (t == LUA_TLIGHTUSERDATA) typename = "light-userdata";
+        s = sdscatprintf(s,"\"%s@%p\"",typename,p);
+        }
+        break;
+    default:
+        s = sdscat(s,"\"<unknown-lua-type>\"");
+        break;
+    }
+    return s;
+}
+
+/* Higher level wrapper for ldbCatStackValueRec() that just uses an initial
+ * recursion level of '0'. */
+sds ldbCatStackValue(sds s, lua_State *lua, int idx) {
+    return ldbCatStackValueRec(s,lua,idx,0);
+}
+
+/* Produce a debugger log entry representing the value of the Lua object
+ * currently on the top of the stack. The element is ot popped nor modified.
+ * Check ldbCatStackValue() for the actual implementation. */
+void ldbLogStackValue(lua_State *lua, char *prefix) {
+    sds s = sdsnew(prefix);
+    s = ldbCatStackValue(s,lua,-1);
+    ldbLogWithMaxLen(s);
+}
+
+char *ldbRedisProtocolToHuman_Int(sds *o, char *reply);
+char *ldbRedisProtocolToHuman_Bulk(sds *o, char *reply);
+char *ldbRedisProtocolToHuman_Status(sds *o, char *reply);
+char *ldbRedisProtocolToHuman_MultiBulk(sds *o, char *reply);
+
+/* Get Redis protocol from 'reply' and appends it in human readable form to
+ * the passed SDS string 'o'.
+ *
+ * Note that the SDS string is passed by reference (pointer of pointer to
+ * char*) so that we can return a modified pointer, as for SDS semantics. */
+char *ldbRedisProtocolToHuman(sds *o, char *reply) {
+    char *p = reply;
+    switch(*p) {
+    case ':': p = ldbRedisProtocolToHuman_Int(o,reply); break;
+    case '$': p = ldbRedisProtocolToHuman_Bulk(o,reply); break;
+    case '+': p = ldbRedisProtocolToHuman_Status(o,reply); break;
+    case '-': p = ldbRedisProtocolToHuman_Status(o,reply); break;
+    case '*': p = ldbRedisProtocolToHuman_MultiBulk(o,reply); break;
+    }
+    return p;
+}
+
+/* The following functions are helpers for ldbRedisProtocolToHuman(), each
+ * take care of a given Redis return type. */
+
+char *ldbRedisProtocolToHuman_Int(sds *o, char *reply) {
+    char *p = strchr(reply+1,'\r');
+    *o = sdscatlen(*o,reply+1,p-reply-1);
+    return p+2;
+}
+
+char *ldbRedisProtocolToHuman_Bulk(sds *o, char *reply) {
+    char *p = strchr(reply+1,'\r');
+    long long bulklen;
+
+    string2ll(reply+1,p-reply-1,&bulklen);
+    if (bulklen == -1) {
+        *o = sdscatlen(*o,"NULL",4);
+        return p+2;
+    } else {
+        *o = sdscatrepr(*o,p+2,bulklen);
+        return p+2+bulklen+2;
+    }
+}
+
+char *ldbRedisProtocolToHuman_Status(sds *o, char *reply) {
+    char *p = strchr(reply+1,'\r');
+
+    *o = sdscatrepr(*o,reply,p-reply);
+    return p+2;
+}
+
+char *ldbRedisProtocolToHuman_MultiBulk(sds *o, char *reply) {
+    char *p = strchr(reply+1,'\r');
+    long long mbulklen;
+    int j = 0;
+
+    string2ll(reply+1,p-reply-1,&mbulklen);
+    p += 2;
+    if (mbulklen == -1) {
+        *o = sdscatlen(*o,"NULL",4);
+        return p;
+    }
+    *o = sdscatlen(*o,"[",1);
+    for (j = 0; j < mbulklen; j++) {
+        p = ldbRedisProtocolToHuman(o,p);
+        if (j != mbulklen-1) *o = sdscatlen(*o,",",1);
+    }
+    *o = sdscatlen(*o,"]",1);
+    return p;
+}
+
+/* Log a Redis reply as debugger output, in an human readable format.
+ * If the resulting string is longer than 'len' plus a few more chars
+ * used as prefix, it gets truncated. */
+void ldbLogRedisReply(char *reply) {
+    sds log = sdsnew("<reply> ");
+    ldbRedisProtocolToHuman(&log,reply);
+    ldbLogWithMaxLen(log);
+}
+
+/* Implements the "print <var>" command of the Lua debugger. It scans for Lua
+ * var "varname" starting from the current stack frame up to the top stack
+ * frame. The first matching variable is printed. */
+void ldbPrint(lua_State *lua, char *varname) {
+    lua_Debug ar;
+
+    int l = 0; /* Stack level. */
+    while (lua_getstack(lua,l,&ar) != 0) {
+        l++;
+        const char *name;
+        int i = 1; /* Variable index. */
+        while((name = lua_getlocal(lua,&ar,i)) != NULL) {
+            i++;
+            if (strcmp(varname,name) == 0) {
+                ldbLogStackValue(lua,"<value> ");
+                lua_pop(lua,1);
+                return;
+            } else {
+                lua_pop(lua,1); /* Discard the var name on the stack. */
+            }
+        }
+    }
+
+    /* Let's try with global vars in two selected cases */
+    if (!strcmp(varname,"ARGV") || !strcmp(varname,"KEYS")) {
+        lua_getglobal(lua, varname);
+        ldbLogStackValue(lua,"<value> ");
+        lua_pop(lua,1);
+    } else {
+        ldbLog(sdsnew("No such variable."));
+    }
+}
+
+/* Implements the "print" command (without arguments) of the Lua debugger.
+ * Prints all the variables in the current stack frame. */
+void ldbPrintAll(lua_State *lua) {
+    lua_Debug ar;
+    int vars = 0;
+
+    if (lua_getstack(lua,0,&ar) != 0) {
+        const char *name;
+        int i = 1; /* Variable index. */
+        while((name = lua_getlocal(lua,&ar,i)) != NULL) {
+            i++;
+            if (!strstr(name,"(*temporary)")) {
+                sds prefix = sdscatprintf(sdsempty(),"<value> %s = ",name);
+                ldbLogStackValue(lua,prefix);
+                sdsfree(prefix);
+                vars++;
+            }
+            lua_pop(lua,1);
+        }
+    }
+
+    if (vars == 0) {
+        ldbLog(sdsnew("No local variables in the current context."));
+    }
+}
+
+/* Implements the break command to list, add and remove breakpoints. */
+void ldbBreak(sds *argv, int argc) {
+    if (argc == 1) {
+        if (ldb.bpcount == 0) {
+            ldbLog(sdsnew("No breakpoints set. Use 'b <line>' to add one."));
+            return;
+        } else {
+            ldbLog(sdscatfmt(sdsempty(),"%i breakpoints set:",ldb.bpcount));
+            int j;
+            for (j = 0; j < ldb.bpcount; j++)
+                ldbLogSourceLine(ldb.bp[j]);
+        }
+    } else {
+        int j;
+        for (j = 1; j < argc; j++) {
+            char *arg = argv[j];
+            long line;
+            if (!string2l(arg,sdslen(arg),&line)) {
+                ldbLog(sdscatfmt(sdsempty(),"Invalid argument:'%s'",arg));
+            } else {
+                if (line == 0) {
+                    ldb.bpcount = 0;
+                    ldbLog(sdsnew("All breakpoints removed."));
+                } else if (line > 0) {
+                    if (ldb.bpcount == LDB_BREAKPOINTS_MAX) {
+                        ldbLog(sdsnew("Too many breakpoints set."));
+                    } else if (ldbAddBreakpoint(line)) {
+                        ldbList(line,1);
+                    } else {
+                        ldbLog(sdsnew("Wrong line number."));
+                    }
+                } else if (line < 0) {
+                    if (ldbDelBreakpoint(-line))
+                        ldbLog(sdsnew("Breakpoint removed."));
+                    else
+                        ldbLog(sdsnew("No breakpoint in the specified line."));
+                }
+            }
+        }
+    }
+}
+
+/* Implements the Lua debugger "eval" command. It just compiles the user
+ * passed fragment of code and executes it, showing the result left on
+ * the stack. */
+void ldbEval(lua_State *lua, sds *argv, int argc) {
+    /* Glue the script together if it is composed of multiple arguments. */
+    sds code = sdsjoinsds(argv+1,argc-1," ",1);
+    sds expr = sdscatsds(sdsnew("return "),code);
+
+    /* Try to compile it as an expression, prepending "return ". */
+    if (luaL_loadbuffer(lua,expr,sdslen(expr),"@ldb_eval")) {
+        lua_pop(lua,1);
+        /* Failed? Try as a statement. */
+        if (luaL_loadbuffer(lua,code,sdslen(code),"@ldb_eval")) {
+            ldbLog(sdscatfmt(sdsempty(),"<error> %s",lua_tostring(lua,-1)));
+            lua_pop(lua,1);
+            sdsfree(code);
+            return;
+        }
+    }
+
+    /* Call it. */
+    sdsfree(code);
+    sdsfree(expr);
+    if (lua_pcall(lua,0,1,0)) {
+        ldbLog(sdscatfmt(sdsempty(),"<error> %s",lua_tostring(lua,-1)));
+        lua_pop(lua,1);
+        return;
+    }
+    ldbLogStackValue(lua,"<retval> ");
+    lua_pop(lua,1);
+}
+
+/* Implement the debugger "redis" command. We use a trick in order to make
+ * the implementation very simple: we just call the Lua redis.call() command
+ * implementation, with ldb.step enabled, so as a side effect the Redis command
+ * and its reply are logged. */
+void ldbRedis(lua_State *lua, sds *argv, int argc) {
+    int j, saved_rc = server.lua_replicate_commands;
+
+    lua_getglobal(lua,"redis");
+    lua_pushstring(lua,"call");
+    lua_gettable(lua,-2);       /* Stack: redis, redis.call */
+    for (j = 1; j < argc; j++)
+        lua_pushlstring(lua,argv[j],sdslen(argv[j]));
+    ldb.step = 1;               /* Force redis.call() to log. */
+    server.lua_replicate_commands = 1;
+    lua_pcall(lua,argc-1,1,0);  /* Stack: redis, result */
+    ldb.step = 0;               /* Disable logging. */
+    server.lua_replicate_commands = saved_rc;
+    lua_pop(lua,2);             /* Discard the result and clean the stack. */
+}
+
+/* Implements "trace" command of the Lua debugger. It just prints a backtrace
+ * querying Lua starting from the current callframe back to the outer one. */
+void ldbTrace(lua_State *lua) {
+    lua_Debug ar;
+    int level = 0;
+
+    while(lua_getstack(lua,level,&ar)) {
+        lua_getinfo(lua,"Snl",&ar);
+        if(strstr(ar.short_src,"user_script") != NULL) {
+            ldbLog(sdscatprintf(sdsempty(),"%s %s:",
+                (level == 0) ? "In" : "From",
+                ar.name ? ar.name : "top level"));
+            ldbLogSourceLine(ar.currentline);
+        }
+        level++;
+    }
+    if (level == 0) {
+        ldbLog(sdsnew("<error> Can't retrieve Lua stack."));
+    }
+}
+
+/* Impleemnts the debugger "maxlen" command. It just queries or sets the
+ * ldb.maxlen variable. */
+void ldbMaxlen(sds *argv, int argc) {
+    if (argc == 2) {
+        int newval = atoi(argv[1]);
+        ldb.maxlen_hint_sent = 1; /* User knows about this command. */
+        if (newval != 0 && newval <= 60) newval = 60;
+        ldb.maxlen = newval;
+    }
+    if (ldb.maxlen) {
+        ldbLog(sdscatprintf(sdsempty(),"<value> replies are truncated at %d bytes.",(int)ldb.maxlen));
+    } else {
+        ldbLog(sdscatprintf(sdsempty(),"<value> replies are unlimited."));
+    }
+}
+
+/* Read debugging commands from client.
+ * Return C_OK if the debugging session is continuing, otherwise
+ * C_ERR if the client closed the connection or is timing out. */
+int ldbRepl(lua_State *lua) {
+    sds *argv;
+    int argc;
+
+    /* We continue processing commands until a command that should return
+     * to the Lua interpreter is found. */
+    while(1) {
+        while((argv = ldbReplParseCommand(&argc)) == NULL) {
+            char buf[1024];
+            int nread = read(ldb.fd,buf,sizeof(buf));
+            if (nread <= 0) {
+                /* Make sure the script runs without user input since the
+                 * client is no longer connected. */
+                ldb.step = 0;
+                ldb.bpcount = 0;
+                return C_ERR;
+            }
+            ldb.cbuf = sdscatlen(ldb.cbuf,buf,nread);
+        }
+
+        /* Flush the old buffer. */
+        sdsfree(ldb.cbuf);
+        ldb.cbuf = sdsempty();
+
+        /* Execute the command. */
+        if (!strcasecmp(argv[0],"h") || !strcasecmp(argv[0],"help")) {
+ldbLog(sdsnew("Redis Lua debugger help:"));
+ldbLog(sdsnew("[h]elp               Show this help."));
+ldbLog(sdsnew("[s]tep               Run current line and stop again."));
+ldbLog(sdsnew("[n]ext               Alias for step."));
+ldbLog(sdsnew("[c]continue          Run till next breakpoint."));
+ldbLog(sdsnew("[l]list              List source code around current line."));
+ldbLog(sdsnew("[l]list [line]       List source code around [line]."));
+ldbLog(sdsnew("                     line = 0 means: current position."));
+ldbLog(sdsnew("[l]list [line] [ctx] In this form [ctx] specifies how many lines"));
+ldbLog(sdsnew("                     to show before/after [line]."));
+ldbLog(sdsnew("[w]hole              List all source code. Alias for 'list 1 1000000'."));
+ldbLog(sdsnew("[p]rint              Show all the local variables."));
+ldbLog(sdsnew("[p]rint <var>        Show the value of the specified variable."));
+ldbLog(sdsnew("                     Can also show global vars KEYS and ARGV."));
+ldbLog(sdsnew("[b]reak              Show all breakpoints."));
+ldbLog(sdsnew("[b]reak <line>       Add a breakpoint to the specified line."));
+ldbLog(sdsnew("[b]reak -<line>      Remove breakpoint from the specified line."));
+ldbLog(sdsnew("[b]reak 0            Remove all breakpoints."));
+ldbLog(sdsnew("[t]race              Show a backtrace."));
+ldbLog(sdsnew("[e]eval <code>       Execute some Lua code (in a different callframe)."));
+ldbLog(sdsnew("[r]edis <cmd>        Execute a Redis command."));
+ldbLog(sdsnew("[m]axlen [len]       Trim logged Redis replies and Lua var dumps to len."));
+ldbLog(sdsnew("                     Specifying zero as <len> means unlimited."));
+ldbLog(sdsnew("[a]abort             Stop the execution of the script. In sync"));
+ldbLog(sdsnew("                     mode dataset changes will be retained."));
+ldbLog(sdsnew(""));
+ldbLog(sdsnew("Debugger functions you can call from Lua scripts:"));
+ldbLog(sdsnew("redis.debug()        Produce logs in the debugger console."));
+ldbLog(sdsnew("redis.breakpoint()   Stop execution like if there was a breakpoing."));
+ldbLog(sdsnew("                     in the next line of code."));
+            ldbSendLogs();
+        } else if (!strcasecmp(argv[0],"s") || !strcasecmp(argv[0],"step") ||
+                   !strcasecmp(argv[0],"n") || !strcasecmp(argv[0],"next")) {
+            ldb.step = 1;
+            break;
+        } else if (!strcasecmp(argv[0],"c") || !strcasecmp(argv[0],"continue")){
+            break;
+        } else if (!strcasecmp(argv[0],"t") || !strcasecmp(argv[0],"trace")) {
+            ldbTrace(lua);
+            ldbSendLogs();
+        } else if (!strcasecmp(argv[0],"m") || !strcasecmp(argv[0],"maxlen")) {
+            ldbMaxlen(argv,argc);
+            ldbSendLogs();
+        } else if (!strcasecmp(argv[0],"b") || !strcasecmp(argv[0],"break")) {
+            ldbBreak(argv,argc);
+            ldbSendLogs();
+        } else if (!strcasecmp(argv[0],"e") || !strcasecmp(argv[0],"eval")) {
+            ldbEval(lua,argv,argc);
+            ldbSendLogs();
+        } else if (!strcasecmp(argv[0],"a") || !strcasecmp(argv[0],"abort")) {
+            lua_pushstring(lua, "script aborted for user request");
+            lua_error(lua);
+        } else if (argc > 1 &&
+                   (!strcasecmp(argv[0],"r") || !strcasecmp(argv[0],"redis"))) {
+            ldbRedis(lua,argv,argc);
+            ldbSendLogs();
+        } else if ((!strcasecmp(argv[0],"p") || !strcasecmp(argv[0],"print"))) {
+            if (argc == 2)
+                ldbPrint(lua,argv[1]);
+            else
+                ldbPrintAll(lua);
+            ldbSendLogs();
+        } else if (!strcasecmp(argv[0],"l") || !strcasecmp(argv[0],"list")){
+            int around = ldb.currentline, ctx = 5;
+            if (argc > 1) {
+                int num = atoi(argv[1]);
+                if (num > 0) around = num;
+            }
+            if (argc > 2) ctx = atoi(argv[2]);
+            ldbList(around,ctx);
+            ldbSendLogs();
+        } else if (!strcasecmp(argv[0],"w") || !strcasecmp(argv[0],"whole")){
+            ldbList(1,1000000);
+            ldbSendLogs();
+        } else {
+            ldbLog(sdsnew("<error> Unknown Redis Lua debugger command or "
+                          "wrong number of arguments."));
+            ldbSendLogs();
+        }
+
+        /* Free the command vector. */
+        sdsfreesplitres(argv,argc);
+    }
+
+    /* Free the current command argv if we break inside the while loop. */
+    sdsfreesplitres(argv,argc);
+    return C_OK;
+}
+
+/* This is the core of our Lua debugger, called each time Lua is about
+ * to start executing a new line. */
+void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
+    lua_getstack(lua,0,ar);
+    lua_getinfo(lua,"Sl",ar);
+    ldb.currentline = ar->currentline;
+
+    int bp = ldbIsBreakpoint(ldb.currentline) || ldb.luabp;
+    int timeout = 0;
+
+    /* Events outside our script are not interesting. */
+    if(strstr(ar->short_src,"user_script") == NULL) return;
+
+    /* Check if a timeout occurred. */
+    if (ar->event == LUA_HOOKCOUNT && ldb.step == 0 && bp == 0) {
+        mstime_t elapsed = mstime() - server.lua_time_start;
+        mstime_t timelimit = server.lua_time_limit ?
+                             server.lua_time_limit : 5000;
+        if (elapsed >= timelimit) {
+            timeout = 1;
+            ldb.step = 1;
+        } else {
+            return; /* No timeout, ignore the COUNT event. */
+        }
+    }
+
+    if (ldb.step || bp) {
+        char *reason = "step over";
+        if (bp) reason = ldb.luabp ? "redis.breakpoint() called" :
+                                     "break point";
+        else if (timeout) reason = "timeout reached, infinite loop?";
+        ldb.step = 0;
+        ldb.luabp = 0;
+        ldbLog(sdscatprintf(sdsempty(),
+            "* Stopped at %d, stop reason = %s",
+            ldb.currentline, reason));
+        ldbLogSourceLine(ldb.currentline);
+        ldbSendLogs();
+        if (ldbRepl(lua) == C_ERR && timeout) {
+            /* If the client closed the connection and we have a timeout
+             * connection, let's kill the script otherwise the process
+             * will remain blocked indefinitely. */
+            lua_pushstring(lua, "timeout during Lua debugging with client closing connection");
+            lua_error(lua);
+        }
+        server.lua_time_start = mstime();
+    }
+}
+
