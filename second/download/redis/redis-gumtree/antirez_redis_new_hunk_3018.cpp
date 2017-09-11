        }
        emptyDb();
        if (rdbLoad(server.dbfilename) != REDIS_OK) {
            addReplyError(c,"Error trying to load the RDB dump");
            return;
        }
        redisLog(REDIS_WARNING,"DB reloaded by DEBUG RELOAD");
