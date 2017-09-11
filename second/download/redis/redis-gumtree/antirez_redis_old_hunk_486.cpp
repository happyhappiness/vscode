/* Called when the user switches from "appendonly no" to "appendonly yes"
 * at runtime using the CONFIG command. */
int startAppendOnly(void) {
    server.aof_last_fsync = server.unixtime;
    server.aof_fd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
    serverAssert(server.aof_state == AOF_OFF);
    if (server.aof_fd == -1) {
        serverLog(LL_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
        return C_ERR;
    }
    if (rewriteAppendOnlyFileBackground() == C_ERR) {
