    removeExpire(c->db,c->argv[1]);
}

void mgetCommand(redisClient *c) {
    int j;

