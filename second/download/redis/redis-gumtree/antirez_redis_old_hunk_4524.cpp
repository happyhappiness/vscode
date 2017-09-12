    sinterGenericCommand(c,c->argv+2,c->argc-2,c->argv[1]);
}

static void flushdbCommand(redisClient *c) {
    dictEmpty(c->db->dict);
    dictEmpty(c->db->expires);
