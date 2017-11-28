static void
doV3Query(int fd, Ip::Address &from, char *buf, icp_common_t header)
{
    /* We have a valid packet */
    char *url = buf + sizeof(icp_common_t) + sizeof(uint32_t);
    HttpRequest *icp_request = icpGetRequest (url, header.reqnum, fd, from);

    if (!icp_request)
        return;

    if (!icpAccessAllowed(from, icp_request)) {
        icpDenyAccess (from, url, header.reqnum, fd);
        delete icp_request;
        return;
    }

    /* The peer is allowed to use this cache */
    ICP3State *state = new ICP3State (header, icp_request);

    state->fd = fd;

    state->from = from;

    state->url = xstrdup (url);

    StoreEntry::getPublic (state, url, METHOD_GET);
}