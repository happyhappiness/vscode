        zmalloc_used_memory() > server.maxmemory)
    {
        addReplyError(c,"command not allowed when used memory > 'maxmemory'");
        resetClient(c);
        return 1;
    }

    /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
