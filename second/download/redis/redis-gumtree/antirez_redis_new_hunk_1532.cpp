        }
    } config_set_memory_field("repl-backlog-size",ll) {
        resizeReplicationBacklog(ll);

    /* Enumeration fields.
     * config_set_enum_field(name,var,enum_var) */
    } config_set_enum_field(
      "loglevel",server.verbosity,loglevel_enum) {
    } config_set_enum_field(
      "maxmemory-policy",server.maxmemory_policy,maxmemory_policy_enum) {
    } config_set_enum_field(
      "appendfsync",server.aof_fsync,aof_fsync_enum) {

    /* Everyhing else is an error... */
    } config_set_else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
        return;
    }

    /* On success we just return a generic OK for all the options. */
    addReply(c,shared.ok);
    return;

