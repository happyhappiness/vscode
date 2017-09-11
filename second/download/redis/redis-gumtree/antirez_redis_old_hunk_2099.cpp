                    old_maxclients, maxfiles);
                redisLog(REDIS_WARNING,"Redis can't set maximum open files "
                    "to %llu because of OS error: %s.",
                    maxfiles, strerror(original_errno));
                redisLog(REDIS_WARNING,"Current maximum open files is %llu. "
                    "maxclients has been reduced to %d to compensate for "
                    "low ulimit. "
