            addReplyError(c,"Error trying to load the RDB dump");
            return;
        }
        serverLog(REDIS_WARNING,"DB reloaded by DEBUG RELOAD");
        addReply(c,shared.ok);
    } else if (!strcasecmp(c->argv[1]->ptr,"loadaof")) {
        emptyDb(NULL);
