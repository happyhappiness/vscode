void
FwdState::connectTimeout(int fd)
{
    FwdServer *fs = servers;

    debugs(17, 2, "fwdConnectTimeout: FD " << fd << ": '" << entry->url() << "'" );
    assert(fd == server_fd);

    if (Config.onoff.log_ip_on_direct && fs->code == HIER_DIRECT && fd_table[fd].ipaddr[0])
        updateHierarchyInfo();

    if (entry->isEmpty()) {
        ErrorState *anErr = errorCon(ERR_CONNECT_FAIL, HTTP_GATEWAY_TIMEOUT, request);
        anErr->xerrno = ETIMEDOUT;
        fail(anErr);
        /*
         * This marks the peer DOWN ...
         */

        if (servers)
            if (servers->_peer)
                peerConnectFailed(servers->_peer);
    }

    comm_close(fd);
}