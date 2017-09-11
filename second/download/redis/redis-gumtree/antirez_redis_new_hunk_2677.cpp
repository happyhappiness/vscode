
    /* AUTH with the master if required. */
    if(server.masterauth) {
        err = sendSynchronousCommand(fd,"AUTH",server.masterauth,NULL);
        if (err) {
            redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",err);
            sdsfree(err);
            goto error;
        }
    }

    /* Set the slave port, so that Master's INFO command can list the
     * slave listening port correctly. */
    {
        sds port = sdsfromlonglong(server.port);
        err = sendSynchronousCommand(fd,"REPLCONF","listening-port",port,
                                         NULL);
        sdsfree(port);
        /* Ignore the error if any, not all the Redis versions support
         * REPLCONF listening-port. */
        if (err) {
            redisLog(REDIS_NOTICE,"(non critical): Master does not understand REPLCONF listening-port: %s", err);
            sdsfree(err);
        }
    }

