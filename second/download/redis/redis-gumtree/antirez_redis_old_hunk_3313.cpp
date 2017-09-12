        return REDIS_OK;
    }

    /* Handle the maxmemory directive.
     *
     * First we try to free some memory if possible (if there are volatile
