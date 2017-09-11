    return C_OK; /* The caller can return, no full resync needed. */

need_full_resync:
    /* We need a full resync for some reason... notify the client. */
    psync_offset = server.master_repl_offset;
    /* Add 1 to psync_offset if it the replication backlog does not exists
     * as when it will be created later we'll increment the offset by one. */
    if (server.repl_backlog == NULL) psync_offset++;
    /* Again, we can't use the connection buffers (see above). */
    buflen = snprintf(buf,sizeof(buf),"+FULLRESYNC %s %lld\r\n",
                      server.runid,psync_offset);
    if (write(c->fd,buf,buflen) != buflen) {
        freeClientAsync(c);
        return C_OK;
    }
    return C_ERR;
}

