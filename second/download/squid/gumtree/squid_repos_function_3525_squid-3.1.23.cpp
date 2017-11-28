void
ConnStateData::clientPinnedConnectionClosed(const CommCloseCbParams &io)
{
    pinning.fd = -1;
    if (pinning.peer) {
        cbdataReferenceDone(pinning.peer);
    }
    safe_free(pinning.host);
    /* NOTE: pinning.pinned should be kept. This combined with fd == -1 at the end of a request indicates that the host
     * connection has gone away */
}