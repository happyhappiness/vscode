    setDeferredMultiBulkLength(c,replylen,matches*2);
}

/*-----------------------------------------------------------------------------
 * CONFIG REWRITE implementation
 *----------------------------------------------------------------------------*/

/* IGNORE:
 *
 * rename-command
 * include
 *
 * Special handling:
 *
 * notify-keyspace-events
 * client-output-buffer-limit
 * save
 * appendonly
 * appendfsync
 * dir
 * maxmemory-policy
 * loglevel
 * unixsocketperm
 * slaveof
 *
 * Type of config directives:
 *
 * CUSTOM
 * VERBATIM
 * YESNO
 * L
 * LL
 *
 */

/* We use the following dictionary type to store where a configuration
 * option is mentioned in the old configuration file, so it's
 * like "maxmemory" -> list of line numbers (first line is zero). */
unsigned int dictSdsHash(const void *key);
int dictSdsKeyCompare(void *privdata, const void *key1, const void *key2);
void dictSdsDestructor(void *privdata, void *val);
void dictListDestructor(void *privdata, void *val);

dictType optionToLineDictType = {
    dictSdsHash,                /* hash function */
    NULL,                       /* key dup */
    NULL,                       /* val dup */
    dictSdsKeyCompare,          /* key compare */
    dictSdsDestructor,          /* key destructor */
    dictListDestructor          /* val destructor */
};

/* The config rewrite state. */
struct rewriteConfigState {
    dict *option_to_line; /* Option -> list of config file lines map */
    int numlines;         /* Number of lines in current config */
    sds *lines;           /* Current lines as an array of sds strings */
    int has_tail;         /* True if we already added directives that were
                             not present in the original config file. */
};

/* Append the new line to the current configuration state. */
void rewriteConfigAppendLine(struct rewriteConfigState *state, sds line) {
    state->lines = zrealloc(state->lines, sizeof(char*) * (state->numlines+1));
    state->lines[state->numlines++] = line;
}

/* Populate the option -> list of line numbers map. */
void rewriteConfigAddLineNumberToOption(struct rewriteConfigState *state, sds option, int linenum) {
    list *l = dictFetchValue(state->option_to_line,option);

    if (l == NULL) {
        l = listCreate();
        dictAdd(state->option_to_line,sdsdup(option),l);
    }
    listAddNodeTail(l,(void*)(long)linenum);
}

/* Read the old file, split it into lines to populate a newly created
 * config rewrite state, and return it to the caller.
 *
 * If it is impossible to read the old file, NULL is returned.
 * If the old file does not exist at all, an empty state is returned. */
struct rewriteConfigState *rewriteConfigReadOldFile(char *path) {
    FILE *fp = fopen(path,"r");
    struct rewriteConfigState *state = zmalloc(sizeof(*state));
    char buf[REDIS_CONFIGLINE_MAX+1];
    int linenum = -1;

    if (fp == NULL && errno != ENOENT) return NULL;

    state->option_to_line = dictCreate(&optionToLineDictType,NULL);
    state->numlines = 0;
    state->lines = NULL;
    state->has_tail = 0;
    if (fp == NULL) return state;

    /* Read the old file line by line, populate the state. */
    while(fgets(buf,REDIS_CONFIGLINE_MAX+1,fp) != NULL) {
        int argc;
        sds *argv;
        sds line = sdstrim(sdsnew(buf),"\r\n\t ");

        linenum++; /* Zero based, so we init at -1 */

        /* Handle comments and empty lines. */
        if (line[0] == '#' || line[0] == '\0') {
            rewriteConfigAppendLine(state,line);
            continue;
        }

        /* Not a comment, split into arguments. */
        argv = sdssplitargs(line,&argc);
        if (argv == NULL) {
            /* Apparently the line is unparsable for some reason, for
             * instance it may have unbalanced quotes. Load it as a
             * comment. */
            sds aux = sdsnew("# ??? ");
            aux = sdscatsds(aux,line);
            sdsfree(line);
            rewriteConfigAppendLine(state,aux);
            continue;
        }

        sdstolower(argv[0]); /* We only want lowercase config directives. */

        /* Now we populate the state according to the content of this line.
         * Append the line and populate the option -> line numbers map. */
        rewriteConfigAppendLine(state,line);
        rewriteConfigAddLineNumberToOption(state,argv[0],linenum);

        sdsfreesplitres(argv,argc);
    }
    fclose(fp);
    return state;
}

/* Rewrite the specified configuration option with the new "line".
 * It progressively uses lines of the file that were already used for the same
 * configuraiton option in the old version of the file, removing that line from
 * the map of options -> line numbers.
 *
 * If there are lines associated with a given configuration option and
 * "force" is non-zero, the line is appended to the configuration file.
 * Usually "force" is true when an option has not its default value, so it
 * must be rewritten even if not present previously.
 * 
 * The first time a line is appended into a configuration file, a comment
 * is added to show that starting from that point the config file was generated
 * by CONFIG REWRITE.
 *
 * "line" is either used, or freed, so the caller does not need to free it
 * in any way. */
void rewriteConfigRewriteLine(struct rewriteConfigState *state, char *option, sds line, int force) {
    sds o = sdsnew(option);
    list *l = dictFetchValue(state->option_to_line,o);

    if (!l && !force) {
        /* Option not used previously, and we are not forced to use it. */
        sdsfree(line);
        sdsfree(o);
        return;
    }

    if (l) {
        listNode *ln = listFirst(l);
        int linenum = (long) ln->value;

        /* There are still lines in the old configuration file we can reuse
         * for this option. Replace the line with the new one. */
        listDelNode(l,ln);
        if (listLength(l) == 0) dictDelete(state->option_to_line,o);
        sdsfree(state->lines[linenum]);
        state->lines[linenum] = line;
    } else {
        /* Append a new line. */
        if (!state->has_tail) {
            rewriteConfigAppendLine(state,
                sdsnew("# Generated by CONFIG REWRITE"));
            state->has_tail = 1;
        }
        rewriteConfigAppendLine(state,line);
    }
    sdsfree(o);
}

/* Rewrite a simple "option-name <bytes>" configuration option. */
void rewriteConfigBytesOption(struct rewriteConfigState *state, char *option, long long value, long long defvalue) {
    int force = value != defvalue;
    /* TODO: check if we can write it using MB, GB, or other suffixes. */
    sds line = sdscatprintf(sdsempty(),"%s %lld",option,value);

    rewriteConfigRewriteLine(state,option,line,force);
}

void rewriteConfigYesNoOption(struct rewriteConfigState *state, char *option, int value, int defvalue) {
    int force = value != defvalue;
    sds line = sdscatprintf(sdsempty(),"%s %s",option,
        value ? "yes" : "no");

    rewriteConfigRewriteLine(state,option,line,force);
}

void rewriteConfigStringOption(struct rewriteConfigState *state, char *option, char *value, char *defvalue) {
    int force = 1;
    sds line;

    /* String options set to NULL need to be not present at all in the
     * configuration file to be set to NULL again at the next reboot. */
    if (value == NULL) return;

    /* Compare the strings as sds strings to have a binary safe comparison. */
    if (defvalue && strcmp(value,defvalue) == 0) force = 0;

    line = sdsnew(option);
    line = sdscatlen(line, " ", 1);
    line = sdscatrepr(line, value, strlen(value));

    rewriteConfigRewriteLine(state,option,line,force);
}

void rewriteConfigNumericalOption(struct rewriteConfigState *state, char *option, long long value, long long defvalue) {
    int force = value != defvalue;
    sds line = sdscatprintf(sdsempty(),"%s %lld",option,value);

    rewriteConfigRewriteLine(state,option,line,force);
}

void rewriteConfigOctalOption(struct rewriteConfigState *state, char *option, int value, int defvalue) {
    int force = value != defvalue;
    sds line = sdscatprintf(sdsempty(),"%s %o",option,value);

    rewriteConfigRewriteLine(state,option,line,force);
}

void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int value, ...) {
    va_list ap;
    char *enum_name, *matching_name;
    int enum_val, def_val, force;
    sds line;
    
    va_start(ap, value);
    while(1) {
        enum_name = va_arg(ap,char*);
        enum_val = va_arg(ap,int);
        if (enum_name == NULL) {
            def_val = enum_val;
            break;
        }
        if (value == enum_val) matching_name = enum_name;
    }
    va_end(ap);
    
    force = value != def_val;
    line = sdscatprintf(sdsempty(),"%s %s",option,matching_name);
    rewriteConfigRewriteLine(state,option,line,force);
}

void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
}

void rewriteConfigSaveOption(struct rewriteConfigState *state) {
}

void rewriteConfigDirOption(struct rewriteConfigState *state) {
}

void rewriteConfigSlaveofOption(struct rewriteConfigState *state) {
}

void rewriteConfigAppendonlyOption(struct rewriteConfigState *state) {
}

void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
}

void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state) {
}

sds rewriteConfigGetContentFromState(struct rewriteConfigState *state) {
    sds content = sdsempty();
    int j;

    for (j = 0; j < state->numlines; j++) {
        content = sdscatsds(content,state->lines[j]);
        content = sdscatlen(content,"\n",1);
    }
    return content;
}

void rewriteConfigReleaseState(struct rewriteConfigState *state) {
    sdsfreesplitres(state->lines,state->numlines);
    dictRelease(state->option_to_line);
    zfree(state);
}

/* Rewrite the configuration file at "path".
 * If the configuration file already exists, we try at best to retain comments
 * and overall structure.
 *
 * Configuration parameters that are at their default value, unless already
 * explicitly included in the old configuration file, are not rewritten.
 *
 * On error -1 is returned and errno is set accordingly, otherwise 0. */
int rewriteConfig(char *path) {
    struct rewriteConfigState *state;
    sds newcontent;

    /* Step 1: read the old config into our rewrite state. */
    if ((state = rewriteConfigReadOldFile(path)) == NULL) return -1;

    /* Step 2: rewrite every single option, replacing or appending it inside
     * the rewrite state. */

    /* TODO: Turn every default into a define, use it also in
     * initServerConfig(). */
    rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
    rewriteConfigStringOption(state,"pidfile",server.pidfile,REDIS_DEFAULT_PID_FILE);
    rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
    rewriteConfigStringOption(state,"bindaddr",server.bindaddr,NULL);
    rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
    rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,0);
    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,0);
    rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,0);
    rewriteConfigEnumOption(state,"loglevel",server.verbosity,
        "debug", REDIS_DEBUG,
        "verbose", REDIS_VERBOSE,
        "notice", REDIS_NOTICE,
        "warning", REDIS_WARNING,
        NULL, REDIS_NOTICE);
    rewriteConfigStringOption(state,"logfile",server.logfile,"stdout");
    rewriteConfigYesNoOption(state,"syslog-enabled",server.syslog_enabled,0);
    rewriteConfigStringOption(state,"syslog-ident",server.syslog_ident,REDIS_DEFAULT_SYSLOG_IDENT);
    rewriteConfigSyslogfacilityOption(state);
    rewriteConfigSaveOption(state);
    rewriteConfigNumericalOption(state,"databases",server.dbnum,REDIS_DEFAULT_DBNUM);
    rewriteConfigYesNoOption(state,"stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err,1);
    rewriteConfigYesNoOption(state,"rdbcompression",server.rdb_compression,1);
    rewriteConfigYesNoOption(state,"rdbchecksum",server.rdb_checksum,1);
    rewriteConfigStringOption(state,"dbfilename",server.rdb_filename,"dump.rdb");
    rewriteConfigDirOption(state);
    rewriteConfigSlaveofOption(state);
    rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
    rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,1);
    rewriteConfigYesNoOption(state,"slave-read-only",server.repl_slave_ro,1);
    rewriteConfigNumericalOption(state,"repl-ping-slave-period",server.repl_ping_slave_period,REDIS_REPL_PING_SLAVE_PERIOD);
    rewriteConfigNumericalOption(state,"repl-timeout",server.repl_timeout,REDIS_REPL_TIMEOUT);
    rewriteConfigNumericalOption(state,"repl-backlog-size",server.repl_backlog_size,REDIS_DEFAULT_REPL_BACKLOG_SIZE);
    rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,REDIS_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
    rewriteConfigNumericalOption(state,"slave-priority",server.slave_priority,REDIS_DEFAULT_SLAVE_PRIORITY);
    rewriteConfigStringOption(state,"requirepass",server.requirepass,NULL);
    rewriteConfigNumericalOption(state,"maxclients",server.maxclients,REDIS_MAX_CLIENTS);
    rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,0);
    rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,
        "volatile-lru", REDIS_MAXMEMORY_VOLATILE_LRU,
        "allkeys-lru", REDIS_MAXMEMORY_ALLKEYS_LRU,
        "volatile-random", REDIS_MAXMEMORY_VOLATILE_RANDOM,
        "allkeys-random", REDIS_MAXMEMORY_ALLKEYS_RANDOM,
        "volatile-ttl", REDIS_MAXMEMORY_VOLATILE_TTL,
        "noeviction", REDIS_MAXMEMORY_NO_EVICTION,
        NULL, REDIS_MAXMEMORY_VOLATILE_LRU);
    rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,3);
    rewriteConfigAppendonlyOption(state);
    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,
        "eveysec", AOF_FSYNC_EVERYSEC,
        "always", AOF_FSYNC_ALWAYS,
        "no", AOF_FSYNC_NO,
        NULL, AOF_FSYNC_EVERYSEC);
    rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,0);
    rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,REDIS_AOF_REWRITE_PERC);
    rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,REDIS_AOF_REWRITE_MIN_SIZE);
    rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,REDIS_LUA_TIME_LIMIT);
    rewriteConfigYesNoOption(state,"cluster-enabled",server.cluster_enabled,0);
    rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,REDIS_DEFAULT_CLUSTER_CONFIG_FILE);
    rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,REDIS_CLUSTER_DEFAULT_NODE_TIMEOUT);
    rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,REDIS_SLOWLOG_LOG_SLOWER_THAN);
    rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,REDIS_SLOWLOG_MAX_LEN);
    rewriteConfigNotifykeyspaceeventsOption(state);
    rewriteConfigNumericalOption(state,"hash-max-ziplist-entries",server.hash_max_ziplist_entries,REDIS_HASH_MAX_ZIPLIST_ENTRIES);
    rewriteConfigNumericalOption(state,"hash-max-ziplist-value",server.hash_max_ziplist_value,REDIS_HASH_MAX_ZIPLIST_VALUE);
    rewriteConfigNumericalOption(state,"list-max-ziplist-entries",server.list_max_ziplist_entries,REDIS_LIST_MAX_ZIPLIST_ENTRIES);
    rewriteConfigNumericalOption(state,"list-max-ziplist-value",server.list_max_ziplist_value,REDIS_LIST_MAX_ZIPLIST_VALUE);
    rewriteConfigNumericalOption(state,"set-max-intset-entries",server.set_max_intset_entries,REDIS_SET_MAX_INTSET_ENTRIES);
    rewriteConfigNumericalOption(state,"zset-max-ziplist-entries",server.zset_max_ziplist_entries,REDIS_ZSET_MAX_ZIPLIST_ENTRIES);
    rewriteConfigNumericalOption(state,"zset-max-ziplist-value",server.zset_max_ziplist_value,REDIS_ZSET_MAX_ZIPLIST_VALUE);
    rewriteConfigYesNoOption(state,"active-rehashing",server.activerehashing,1);
    rewriteConfigClientoutputbufferlimitOption(state);
    rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
    rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,1);

    /* Step 3: remove all the orphaned lines in the old file, that is, lines
     * that were used by a config option and are no longer used, like in case
     * of multiple "save" options or duplicated options. */
//    rewriteConfigRemoveOrphaned(state);

    /* Step 4: generate a new configuration file from the modified state
     * and write it into the original file. */
    newcontent = rewriteConfigGetContentFromState(state);
    printf("%s\n", newcontent);

    sdsfree(newcontent);
    rewriteConfigReleaseState(state);
    return 0;
}

/*-----------------------------------------------------------------------------
 * CONFIG command entry point
 *----------------------------------------------------------------------------*/

void configCommand(redisClient *c) {
    if (!strcasecmp(c->argv[1]->ptr,"set")) {
        if (c->argc != 4) goto badarity;
