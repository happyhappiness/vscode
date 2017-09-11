    }
}

void bgsaveCommand(client *c) {
    if (server.rdb_child_pid != -1) {
        addReplyError(c,"Background save already in progress");
    } else if (server.aof_child_pid != -1) {
        addReplyError(c,"Can't BGSAVE while AOF log rewriting is in progress");
    } else if (rdbSaveBackground(server.rdb_filename) == C_OK) {
        addReplyStatus(c,"Background saving started");
    } else {
