 * CONFIG SET implementation
 *----------------------------------------------------------------------------*/

void configSetCommand(redisClient *c) {
    robj *o;
    long long ll;
    int err;
    redisAssertWithInfo(c,c->argv[2],sdsEncodedObject(c->argv[2]));
    redisAssertWithInfo(c,c->argv[3],sdsEncodedObject(c->argv[3]));
    o = c->argv[3];

    if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
        if (!pathIsBaseName(o->ptr)) {
            addReplyError(c, "dbfilename can't be a path, just a filename");
            return;
