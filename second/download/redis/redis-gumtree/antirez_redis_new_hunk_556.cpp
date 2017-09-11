
    /* Read the RESTORE replies. */
    int error_from_target = 0;
    int del_idx = 1; /* Index of the key argument for the replicated DEL op. */
    robj **newargv;

    if (!copy) newargv = zmalloc(sizeof(robj*)*(num_keys+1));

    for (j = 0; j < num_keys; j++) {
        if (syncReadLine(cs->fd, buf2, sizeof(buf2), timeout) <= 0)
            goto socket_err;
        if ((select && buf1[0] == '-') || buf2[0] == '-') {
            /* On error assume that last_dbid is no longer valid. */
            if (!error_from_target) {
                cs->last_dbid = -1;
                addReplyErrorFormat(c,"Target instance replied with error: %s",
                    (select && buf1[0] == '-') ? buf1+1 : buf2+1);
                error_from_target = 1;
            }
        } else {
            if (!copy) {
                robj *aux;
