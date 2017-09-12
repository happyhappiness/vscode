            id[len] = '\0';
            if (atoi(id) != dbid) continue; /* skip this file */
        }
        
        /* Finally unlink the file */
        snprintf(buf,1024,"%s/%s",path,dp->d_name);
        if (unlink(buf) == -1) {
            redisLog(REDIS_WARNING,
                "Can't unlink %s: %s", buf, strerror(errno));
            redisPanic("Unrecoverable Disk store errore. Existing.");
        }
    }
