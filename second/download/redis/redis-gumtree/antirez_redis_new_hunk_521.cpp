 * It is very common for the cached socket to get closed, if just reopening
 * it works it's a shame to notify the error to the caller. */
socket_err:
    /* Cleanup we want to perform in both the retry and no retry case.
     * Note: Closing the migrate socket will also force SELECT next time. */
    sdsfree(cmd.io.buffer.ptr);
    migrateCloseSocket(c->argv[1],c->argv[2]);
    zfree(newargv);
    newargv = NULL; /* This will get reallocated on retry. */

    /* Retry only if it's not a timeout and we never attempted a retry
     * (or the code jumping here did not set may_retry to zero). */
    if (errno != ETIMEDOUT && may_retry) {
        may_retry = 0;
        goto try_again;
    }

    /* Cleanup we want to do if no retry is attempted. */
    zfree(ov); zfree(kv);
    addReplySds(c,
        sdscatprintf(sdsempty(),
            "-IOERR error or timeout %s to target instance\r\n",
