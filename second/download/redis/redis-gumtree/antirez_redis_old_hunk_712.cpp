 *                   offset is saved.
 * PSYNC_NOT_SUPPORTED: If the server does not understand PSYNC at all and
 *                      the caller should fall back to SYNC.
 */

#define PSYNC_CONTINUE 0
#define PSYNC_FULLRESYNC 1
#define PSYNC_NOT_SUPPORTED 2
int slaveTryPartialResynchronization(int fd) {
    char *psync_runid;
    char psync_offset[32];
    sds reply;

    /* Initially set repl_master_initial_offset to -1 to mark the current
     * master run_id and offset as not valid. Later if we'll be able to do
     * a FULL resync using the PSYNC command we'll set the offset at the
     * right value, so that this information will be propagated to the
     * client structure representing the master into server.master. */
    server.repl_master_initial_offset = -1;

    if (server.cached_master) {
        psync_runid = server.cached_master->replrunid;
        snprintf(psync_offset,sizeof(psync_offset),"%lld", server.cached_master->reploff+1);
        serverLog(LL_NOTICE,"Trying a partial resynchronization (request %s:%s).", psync_runid, psync_offset);
    } else {
        serverLog(LL_NOTICE,"Partial resynchronization not possible (no cached master)");
        psync_runid = "?";
        memcpy(psync_offset,"-1",3);
    }

    /* Issue the PSYNC command */
    reply = sendSynchronousCommand(fd,"PSYNC",psync_runid,psync_offset,NULL);

    if (!strncmp(reply,"+FULLRESYNC",11)) {
        char *runid = NULL, *offset = NULL;
