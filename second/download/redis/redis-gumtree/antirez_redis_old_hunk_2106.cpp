            }
            if (f < oldlimit) f = oldlimit;
            if (f != maxfiles) {
                server.maxclients = f-REDIS_EVENTLOOP_FDSET_INCR;
                redisLog(REDIS_WARNING,"Unable to set the max number of files limit to %d (%s), setting the max clients configuration to %d.",
                    (int) maxfiles, strerror(errno), (int) server.maxclients);
            } else {
                redisLog(REDIS_NOTICE,"Max number of open files set to %d",
                    (int) maxfiles);
            }
        }
    }
