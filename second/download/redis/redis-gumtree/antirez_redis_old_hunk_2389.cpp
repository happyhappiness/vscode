            return;
        }
    }
    if (prepareForShutdown(flags) == REDIS_OK) exit(0);
    addReplyError(c,"Errors trying to SHUTDOWN. Check logs.");
}
