    }

    /* If the list is empty or the key does not exists we must block */
    timeout = lltimeout;
    if (timeout > 0) timeout += time(NULL);
    blockForKeys(c,c->argv+1,c->argc-2,timeout);
}

void blpopCommand(redisClient *c) {
