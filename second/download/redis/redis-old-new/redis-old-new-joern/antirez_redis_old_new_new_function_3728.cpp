void dbsizeCommand(redisClient *c) {
    addReplyLongLong(c,dictSize(c->db->dict));
}