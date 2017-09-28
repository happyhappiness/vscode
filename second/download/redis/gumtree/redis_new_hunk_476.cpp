}

/*-----------------------------------------------------------------------------
 * CONFIG SET implementation
 *----------------------------------------------------------------------------*/

#define config_set_bool_field(_name,_var) \
    } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
        int yn = yesnotoi(o->ptr); \
        if (yn == -1) goto badfmt; \
        _var = yn;

#define config_set_numerical_field(_name,_var,min,max) \
    } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
        if (getLongLongFromObject(o,&ll) == C_ERR || ll < 0) goto badfmt; \
        if (min != LLONG_MIN && ll < min) goto badfmt; \
        if (max != LLONG_MAX && ll > max) goto badfmt; \
        _var = ll;

#define config_set_memory_field(_name,_var) \
    } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
        ll = memtoll(o->ptr,&err); \
        if (err || ll < 0) goto badfmt; \
        _var = ll;

#define config_set_enum_field(_name,_var,_enumvar) \
    } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
        int enumval = configEnumGetValue(_enumvar,o->ptr); \
        if (enumval == INT_MIN) goto badfmt; \
        _var = enumval;

#define config_set_special_field(_name) \
    } else if (!strcasecmp(c->argv[2]->ptr,_name)) {

#define config_set_else } else

void configSetCommand(client *c) {
    robj *o;
    long long ll;
    int err;
    serverAssertWithInfo(c,c->argv[2],sdsEncodedObject(c->argv[2]));
    serverAssertWithInfo(c,c->argv[3],sdsEncodedObject(c->argv[3]));
    o = c->argv[3];

    if (0) { /* this starts the config_set macros else-if chain. */

    /* Special fields that can't be handled with general macros. */
    config_set_special_field("dbfilename") {
        if (!pathIsBaseName(o->ptr)) {
            addReplyError(c, "dbfilename can't be a path, just a filename");
            return;
        }
        zfree(server.rdb_filename);
        server.rdb_filename = zstrdup(o->ptr);
    } config_set_special_field("requirepass") {
        if (sdslen(o->ptr) > CONFIG_AUTHPASS_MAX_LEN) goto badfmt;
        zfree(server.requirepass);
        server.requirepass = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
    } config_set_special_field("masterauth") {
        zfree(server.masterauth);
        server.masterauth = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
    } config_set_special_field("maxclients") {
        int orig_value = server.maxclients;

        if (getLongLongFromObject(o,&ll) == C_ERR || ll < 1) goto badfmt;

        /* Try to check if the OS is capable of supporting so many FDs. */
        server.maxclients = ll;
        if (ll > orig_value) {
            adjustOpenFilesLimit();
            if (server.maxclients != ll) {
                addReplyErrorFormat(c,"The operating system is not able to handle the specified number of clients, try with %d", server.maxclients);
                server.maxclients = orig_value;
                return;
            }
            if ((unsigned int) aeGetSetSize(server.el) <
                server.maxclients + CONFIG_FDSET_INCR)
            {
                if (aeResizeSetSize(server.el,
                    server.maxclients + CONFIG_FDSET_INCR) == AE_ERR)
                {
                    addReplyError(c,"The event loop API used by Redis is not able to handle the specified number of clients");
                    server.maxclients = orig_value;
                    return;
                }
            }
        }
    } config_set_special_field("appendonly") {
        int enable = yesnotoi(o->ptr);

        if (enable == -1) goto badfmt;
        if (enable == 0 && server.aof_state != AOF_OFF) {
            stopAppendOnly();
        } else if (enable && server.aof_state == AOF_OFF) {
            if (startAppendOnly() == C_ERR) {
                addReplyError(c,
                    "Unable to turn on AOF. Check server logs.");
                return;
            }
        }
    } config_set_special_field("save") {
        int vlen, j;
        sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);

        /* Perform sanity check before setting the new config:
         * - Even number of args
         * - Seconds >= 1, changes >= 0 */
