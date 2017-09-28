    sdsfree(bitcounters);
    if (o) decrRefCount(o);
}

/* PFDEBUG <subcommand> <key> ... args ...
 * Different debugging related operations about the HLL implementation. */
void pfdebugCommand(redisClient *c) {
    char *cmd = c->argv[1]->ptr;
    struct hllhdr *hdr;
    robj *o;
    int j;

    o = lookupKeyRead(c->db,c->argv[2]);
    if (o == NULL) {
        addReplyError(c,"The specified key does not exist");
        return;
    }
    if (isHLLObjectOrReply(c,o) != REDIS_OK) return;
    o = dbUnshareStringValue(c->db,c->argv[2],o);
    hdr = o->ptr;

    /* PFDEBUG GETREG <key> */
    if (!strcasecmp(cmd,"getreg")) {
        if (c->argc != 3) goto arityerr;

        if (hdr->encoding == HLL_SPARSE) {
            if (hllSparseToDense(o) == REDIS_ERR) {
                addReplySds(c,sdsnew(invalid_hll_err));
                return;
            }
            server.dirty++; /* Force propagation on encoding change. */
        }

