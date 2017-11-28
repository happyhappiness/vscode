bool HttpStateData::peerSupportsConnectionPinning() const
{
    const HttpReply *rep = entry->mem_obj->getReply();
    const HttpHeader *hdr = &rep->header;
    bool rc;
    String header;

    if (!_peer)
        return true;

    /*If this peer does not support connection pinning (authenticated
      connections) return false
     */
    if (!_peer->connection_auth)
        return false;

    /*The peer supports connection pinning and the http reply status
      is not unauthorized, so the related connection can be pinned
     */
    if (rep->sline.status() != Http::scUnauthorized)
        return true;

    /*The server respond with Http::scUnauthorized and the peer configured
      with "connection-auth=on" we know that the peer supports pinned
      connections
    */
    if (_peer->connection_auth == 1)
        return true;

    /*At this point peer has configured with "connection-auth=auto"
      parameter so we need some extra checks to decide if we are going
      to allow pinned connections or not
    */

    /*if the peer configured with originserver just allow connection
        pinning (squid 2.6 behaviour)
     */
    if (_peer->options.originserver)
        return true;

    /*if the connections it is already pinned it is OK*/
    if (request->flags.pinned)
        return true;

    /*Allow pinned connections only if the Proxy-support header exists in
      reply and has in its list the "Session-Based-Authentication"
      which means that the peer supports connection pinning.
     */
    if (!hdr->has(HDR_PROXY_SUPPORT))
        return false;

    header = hdr->getStrOrList(HDR_PROXY_SUPPORT);
    /* XXX This ought to be done in a case-insensitive manner */
    rc = (strstr(header.termedBuf(), "Session-Based-Authentication") != NULL);

    return rc;
}