/* ========================= Type agnostic commands ========================= */

static void delCommand(redisClient *c) {
    if (deleteKey(c->db,c->argv[1])) {
        server.dirty++;
        addReply(c,shared.cone);
    } else {
        addReply(c,shared.czero);
    }
}

