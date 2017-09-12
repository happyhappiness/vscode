    }
    touchWatchedKey(c->db,c->argv[1]);
    server.dirty++;
    addReplyLongLong(c,totlen);
}

void substrCommand(redisClient *c) {
