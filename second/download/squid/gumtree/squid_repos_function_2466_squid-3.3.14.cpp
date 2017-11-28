void
getOutgoingAddress(HttpRequest * request, Comm::ConnectionPointer conn)
{
    // skip if an outgoing address is already set.
    if (!conn->local.IsAnyAddr()) return;

    // ensure that at minimum the wildcard local matches remote protocol
    if (conn->remote.IsIPv4())
        conn->local.SetIPv4();

    // maybe use TPROXY client address
    if (request && request->flags.spoofClientIp) {
        if (!conn->getPeer() || !conn->getPeer()->options.no_tproxy) {
#if FOLLOW_X_FORWARDED_FOR && LINUX_NETFILTER
            if (Config.onoff.tproxy_uses_indirect_client)
                conn->local = request->indirect_client_addr;
            else
#endif
                conn->local = request->client_addr;
            // some flags need setting on the socket to use this address
            conn->flags |= COMM_DOBIND;
            conn->flags |= COMM_TRANSPARENT;
            return;
        }
        // else no tproxy today ...
    }

    if (!Config.accessList.outgoing_address) {
        return; // anything will do.
    }

    ACLFilledChecklist ch(NULL, request, NULL);
    ch.dst_peer = conn->getPeer();
    ch.dst_addr = conn->remote;

    // TODO use the connection details in ACL.
    // needs a bit of rework in ACLFilledChecklist to use Comm::Connection instead of ConnStateData

    AclAddress *l;
    for (l = Config.accessList.outgoing_address; l; l = l->next) {

        /* check if the outgoing address is usable to the destination */
        if (conn->remote.IsIPv4() != l->addr.IsIPv4()) continue;

        /* check ACLs for this outgoing address */
        if (!l->aclList || ch.fastCheck(l->aclList) == ACCESS_ALLOWED) {
            conn->local = l->addr;
            return;
        }
    }
}