 * CONFIG SET implementation
 *----------------------------------------------------------------------------*/

void configSetCommand(redisClient *c) {
    robj *o;
    long long ll;
    redisAssertWithInfo(c,c->argv[2],c->argv[2]->encoding == REDIS_ENCODING_RAW);
    redisAssertWithInfo(c,c->argv[2],c->argv[3]->encoding == REDIS_ENCODING_RAW);
    o = c->argv[3];

    if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
        if (!pathIsBaseName(o->ptr)) {
            addReplyError(c, "dbfilename can't be a path, just a filename");
            return;
