void
FwdState::updateHierarchyInfo()
{
    assert(request);

    FwdServer *fs = servers;
    assert(fs);

    const char *nextHop = NULL;

    if (fs->_peer) {
        // went to peer, log peer host name
        nextHop = fs->_peer->name;
    } else {
        // went DIRECT, must honor log_ip_on_direct

        // XXX: or should we use request->host_addr here? how?
        assert(server_fd >= 0);
        nextHop = fd_table[server_fd].ipaddr;
        if (!Config.onoff.log_ip_on_direct || !nextHop[0])
            nextHop = request->GetHost(); // domain name
    }

    assert(nextHop);
    hierarchyNote(&request->hier, fs->code, nextHop);
}