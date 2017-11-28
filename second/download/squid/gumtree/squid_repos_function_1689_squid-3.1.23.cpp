inline void clear() {
        timeoutHandler = NULL;
        closeHandler = NULL;
        halfClosedReader = NULL;
        // XXX: the following memset may corrupt or leak new or changed members
        memset(this, 0, sizeof(fde));
        local_addr.SetEmpty(); // IpAddress likes to be setup nicely.
    }