void
FwdState::connectDone(int aServerFD, const DnsLookupDetails &dns, comm_err_t status, int xerrno)
{
    FwdServer *fs = servers;
    assert(server_fd == aServerFD);

    request->recordLookup(dns);

    if (Config.onoff.log_ip_on_direct && status != COMM_ERR_DNS && fs->code == HIER_DIRECT)
        updateHierarchyInfo();

    if (status == COMM_ERR_DNS) {
        /*
         * Only set the dont_retry flag if the DNS lookup fails on
         * a direct connection.  If DNS lookup fails when trying
         * a neighbor cache, we may want to retry another option.
         */

        if (NULL == fs->_peer)
            flags.dont_retry = 1;

        debugs(17, 4, "fwdConnectDone: Unknown host: " << request->GetHost());

        ErrorState *const anErr = makeConnectingError(ERR_DNS_FAIL);

        anErr->dnsError = dns.error;

        fail(anErr);

        comm_close(server_fd);
    } else if (status != COMM_OK) {
        assert(fs);
        ErrorState *const anErr = makeConnectingError(ERR_CONNECT_FAIL);
        anErr->xerrno = xerrno;

        fail(anErr);

        if (fs->_peer)
            peerConnectFailed(fs->_peer);

        comm_close(server_fd);
    } else {
        debugs(17, 3, "fwdConnectDone: FD " << server_fd << ": '" << entry->url() << "'" );

        if (fs->_peer)
            peerConnectSucceded(fs->_peer);

#if USE_SSL

        if ((fs->_peer && fs->_peer->use_ssl) ||
                (!fs->_peer && request->protocol == PROTO_HTTPS)) {
            if (fs->code != PINNED) {
                initiateSSL();
                return;
            }
        }

#endif
        dispatch();
    }
}