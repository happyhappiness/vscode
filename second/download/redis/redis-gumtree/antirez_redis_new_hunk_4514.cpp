/* ========================= Type agnostic commands ========================= */

static void delCommand(redisClient *c) {
    int deleted = 0, j;

    for (j = 1; j < c->argc; j++) {
        if (deleteKey(c->db,c->argv[j])) {
            server.dirty++;
            deleted++;
        }
    }
    switch(deleted) {
    case 0:
        addReply(c,shared.czero);
        break;
    case 1:
        addReply(c,shared.cone);
        break;
    default:
        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",deleted));
        break;
    }
}

