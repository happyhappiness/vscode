static int
ignoreMulticastReply(peer * p, MemObject * mem)
{
    if (p == NULL)
        return 0;

    if (!p->options.mcast_responder)
        return 0;

    if (peerHTTPOkay(p, mem->request))
        return 0;

    return 1;
}