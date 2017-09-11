                limit.rlim_cur = f;
                limit.rlim_max = f;
                if (setrlimit(RLIMIT_NOFILE,&limit) != -1) break;
                f -= REDIS_EVENTLOOP_FDSET_INCR;
            }
            if (f < oldlimit) f = oldlimit;
            if (f != maxfiles) {
                server.maxclients = f-REDIS_EVENTLOOP_FDSET_INCR;
                redisLog(REDIS_WARNING,"Unable to set the max number of files limit to %d (%s), setting the max clients configuration to %d.",
                    (int) maxfiles, strerror(errno), (int) server.maxclients);
            } else {
