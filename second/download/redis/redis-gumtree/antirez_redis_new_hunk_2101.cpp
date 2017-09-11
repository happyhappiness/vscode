                limit.rlim_cur = f;
                limit.rlim_max = f;
                if (setrlimit(RLIMIT_NOFILE,&limit) != -1) break;
                f -= REDIS_MIN_RESERVED_FDS;
                if (f > limit.rlim_cur) {
                    /* Instead of getting smaller, f just got bigger.
                     * That means it wrapped around its unsigned floor
                     * and is now closer to 2^64.  We can't help anymore. */
                    redisLog(REDIS_WARNING,"Failed to set max file limit. "
                        "You requested maxclients of %d "
                        "but your 'ulimit -n' is set to %llu. "
                        "Please increase your 'ulimit -n' to at least %llu.",
                        server.maxclients, oldlimit, maxfiles);
                    exit(1);
                }
            }
            if (f < oldlimit) f = oldlimit;
            if (f != maxfiles) {
                int old_maxclients = server.maxclients;
                int original_errno = errno;
                server.maxclients = f-REDIS_MIN_RESERVED_FDS;
                if (server.maxclients < 1) {
                    redisLog(REDIS_WARNING,"Your current 'ulimit -n' "
                        "of %llu is not enough for Redis to start. "
                        "Please increase your open file limit to at least "
                        "%llu. Exiting.", oldlimit, maxfiles);
                    exit(1);
                }
                redisLog(REDIS_WARNING,"You requested maxclients of %d "
                    "requiring at least %llu max file descriptors.",
                    old_maxclients, maxfiles);
                redisLog(REDIS_WARNING,"Redis can't set maximum open files "
                    "to %llu because of OS error: %s.",
                    maxfiles, strerror(original_errno));
                redisLog(REDIS_WARNING,"Current maximum open files is %llu. "
                    "maxclients has been reduced to %d to compensate for "
                    "low ulimit. "
                    "If you need higher maxclients increase 'ulimit -n'.",
                    oldlimit, server.maxclients);
            } else {
                redisLog(REDIS_NOTICE,"Increased maximum number of open files "
                    "to %llu (it was originally set to %llu).",
                    maxfiles, oldlimit);
            }
        }
    }
