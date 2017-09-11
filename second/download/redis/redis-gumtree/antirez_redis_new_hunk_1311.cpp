        sds client = catClientInfoString(sdsempty(),c);

        freeClientAsync(c);
        serverLog(REDIS_WARNING,"Client %s scheduled to be closed ASAP for overcoming of output buffer limits.", client);
        sdsfree(client);
    }
}
