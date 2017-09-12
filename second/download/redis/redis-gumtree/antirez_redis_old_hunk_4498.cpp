static void debugCommand(redisClient *c) {
    if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
        *((char*)-1) = 'x';
    } else {
        addReplySds(c,sdsnew("-ERR Syntax error, try DEBUG SEGFAULT\r\n"));
    }
}

