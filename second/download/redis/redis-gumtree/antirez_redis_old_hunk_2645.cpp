        return;
    }

    redisLog(REDIS_NOTICE,"Non blocking connect for SYNC fired the event.");
    /* This event should only be triggered once since it is used to have a
     * non-blocking connect(2) to the master. It has been triggered when this
     * function is called, so we can delete it. */
    aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);

    /* AUTH with the master if required. */
    if(server.masterauth) {
