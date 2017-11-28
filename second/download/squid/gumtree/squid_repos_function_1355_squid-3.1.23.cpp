void
icpDenyAccess(IpAddress &from, char *url, int reqnum, int fd)
{
    debugs(12, 2, "icpDenyAccess: Access Denied for " << from << " by " << AclMatchedName << ".");

    if (clientdbCutoffDenied(from)) {
        /*
         * count this DENIED query in the clientdb, even though
         * we're not sending an ICP reply...
         */
        clientdbUpdate(from, LOG_UDP_DENIED, PROTO_ICP, 0);
    } else {
        icpCreateAndSend(ICP_DENIED, 0, url, reqnum, 0, fd, from);
    }
}