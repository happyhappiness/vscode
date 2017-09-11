    return o;
}

/* Check if the object is a String of REDIS_HLL_SIZE bytes.
 * Return REDIS_OK if this is true, otherwise reply to the client
 * with an error and return REDIS_ERR. */
int isHLLObjectOrReply(redisClient *c, robj *o) {
    /* Key exists, check type */
    if (checkType(c,o,REDIS_STRING))
        return REDIS_ERR; /* Error already sent. */

    /* If this is a string representing an HLL, the size should match
     * exactly. */
    if (stringObjectLen(o) != REDIS_HLL_SIZE) {
        addReplyErrorFormat(c, "Key is not a valid HyperLogLog string value.");
        return REDIS_ERR;
    }
    return REDIS_OK;
}

/* PFADD var ele ele ele ... ele => :0 or :1 */
void pfaddCommand(redisClient *c) {
    robj *o = lookupKeyWrite(c->db,c->argv[1]);
