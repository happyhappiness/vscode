            call_uname = 0;
        }

        unsigned int lruclock;
        atomicGet(server.lruclock,lruclock);
        info = sdscatprintf(info,
            "# Server\r\n"
            "redis_version:%s\r\n"
