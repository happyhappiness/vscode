 */
static int dav_handler(request_rec *r)
{
    if (strcmp(r->handler, DAV_HANDLER_NAME) != 0)
        return DECLINED;

    /* ### do we need to do anything with r->proxyreq ?? */

    /*
     * ### anything else to do here? could another module and/or
     * ### config option "take over" the handler here? i.e. how do
     * ### we lock down this hierarchy so that we are the ultimate
