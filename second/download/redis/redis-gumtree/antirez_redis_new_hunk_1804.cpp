        if (childpid == -1) {
            redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
                strerror(errno));
            zfree(fds);
            close(pipefds[0]);
            close(pipefds[1]);
            return REDIS_ERR;
        }
        redisLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);
