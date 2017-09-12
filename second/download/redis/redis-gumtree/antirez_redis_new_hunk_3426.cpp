            id[len] = '\0';
            if (atoi(id) != dbid) continue; /* skip this file */
        }
        if (unlink(dp->d_name) == -1) {
            redisLog(REDIS_WARNING,
                "Can't unlink %s: %s", path, strerror(errno));
            redisPanic("Unrecoverable Disk store errore. Existing.");
