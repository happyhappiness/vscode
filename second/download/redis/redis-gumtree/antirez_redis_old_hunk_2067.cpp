    return o;
}

/* PFADD var ele ele ele ... ele => :0 or :1 */
void pfaddCommand(redisClient *c) {
    robj *o = lookupKeyWrite(c->db,c->argv[1]);
