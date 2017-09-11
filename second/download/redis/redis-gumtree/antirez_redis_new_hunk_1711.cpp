 * A Peer ID always fits inside a buffer of REDIS_PEER_ID_LEN bytes, including
 * the null term.
 *
 * On failure the function still populates 'peerid' with the "?:0" string
 * in case you want to relax error checking or need to display something
 * anyway (see anetPeerToString implementation for more info). */
static void genClientPeerId(redisClient *client, char *peerid,
                            size_t peerid_len) {
    if (client->flags & REDIS_UNIX_SOCKET) {
        /* Unix socket client. */
        snprintf(peerid,peerid_len,"%s:0",server.unixsocket);
    } else {
        /* TCP client. */
        anetFormatPeer(client->fd,peerid,peerid_len);
    }
}

