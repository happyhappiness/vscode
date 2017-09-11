        size_t authlen;

        authlen = snprintf(authcmd,sizeof(authcmd),"AUTH %s\r\n",server.masterauth);
        if (syncWrite(fd,authcmd,authlen,server.repl_syncio_timeout*1000) == -1) {
            redisLog(REDIS_WARNING,"Unable to AUTH to MASTER: %s",
                strerror(errno));
            goto error;
        }
        /* Read the AUTH result.  */
        if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout*1000) == -1) {
            redisLog(REDIS_WARNING,"I/O error reading auth result from MASTER: %s",
                strerror(errno));
            goto error;
