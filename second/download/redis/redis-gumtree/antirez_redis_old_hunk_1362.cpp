        if (syncReadLine(fd,buf,sizeof(buf),
            server.repl_syncio_timeout*1000) == -1)
        {
            redisLog(REDIS_WARNING,
                "I/O error reading PING reply from master: %s",
                strerror(errno));
            goto error;
