Comm::ConnectionPointer
FwdState::pconnPop(const Comm::ConnectionPointer &dest, const char *domain)
{
    bool retriable = checkRetriable();
    if (!retriable && Config.accessList.serverPconnForNonretriable) {
        ACLFilledChecklist ch(Config.accessList.serverPconnForNonretriable, request, NULL);
        retriable = ch.fastCheck().allowed();
    }
    // always call shared pool first because we need to close an idle
    // connection there if we have to use a standby connection.
    Comm::ConnectionPointer conn = fwdPconnPool->pop(dest, domain, retriable);
    if (!Comm::IsConnOpen(conn)) {
        // either there was no pconn to pop or this is not a retriable xaction
        if (CachePeer *peer = dest->getPeer()) {
            if (peer->standby.pool)
                conn = peer->standby.pool->pop(dest, domain, true);
        }
    }
    return conn; // open, closed, or nil
}