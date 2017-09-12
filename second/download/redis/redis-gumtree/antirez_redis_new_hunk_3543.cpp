    }

    /* If the list is empty or the key does not exists we must block */
    if (timeout > 0) timeout += time(NULL);
    blockForKeys(c, c->argv + 1, c->argc - 2, timeout, NULL);
}

int checkTimeout(redisClient *c, robj *object, time_t *timeout) {
    long long lltimeout;

    if (getLongLongFromObject(object, &lltimeout) != REDIS_OK) {
      addReplyError(c, "timeout is not an integer");
      return REDIS_ERR;
    }
    
    if (lltimeout < 0) {
      addReplyError(c, "timeout is negative");
      return REDIS_ERR;
    }

    *timeout = lltimeout;

    return REDIS_OK;
}

void blpopCommand(redisClient *c) {
