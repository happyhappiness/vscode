static void
peerSelectDnsResults(const ipcache_addrs *ia, const DnsLookupDetails &details, void *data)
{
    ps_state *psstate = (ps_state *)data;

    if (!cbdataReferenceValid(psstate->callback_data)) {
        debugs(44, 3, "Aborting peer selection. Parent Job went away.");
        delete psstate;
        return;
    }

    psstate->request->recordLookup(details);

    FwdServer *fs = psstate->servers;
    if (ia != NULL) {

        assert(ia->cur < ia->count);

        // loop over each result address, adding to the possible destinations.
        int ip = ia->cur;
        for (int n = 0; n < ia->count; ++n, ++ip) {
            Comm::ConnectionPointer p;

            if (ip >= ia->count) ip = 0; // looped back to zero.

            // Enforce forward_max_tries configuration.
            if (psstate->paths->size() >= (unsigned int)Config.forward_max_tries)
                break;

            // for TPROXY spoofing we must skip unusable addresses.
            if (psstate->request->flags.spoofClientIp && !(fs->_peer && fs->_peer->options.no_tproxy) ) {
                if (ia->in_addrs[ip].isIPv4() != psstate->request->client_addr.isIPv4()) {
                    // we CAN'T spoof the address on this link. find another.
                    continue;
                }
            }

            p = new Comm::Connection();
            p->remote = ia->in_addrs[ip];

            // when IPv6 is disabled we cannot use it
            if (!Ip::EnableIpv6 && p->remote.isIPv6()) {
                const char *host = (fs->_peer ? fs->_peer->host : psstate->request->GetHost());
                ipcacheMarkBadAddr(host, p->remote);
                continue;
            }

            if (fs->_peer)
                p->remote.port(fs->_peer->http_port);
            else
                p->remote.port(psstate->request->port);
            p->peerType = fs->code;
            p->setPeer(fs->_peer);

            // check for a configured outgoing address for this destination...
            getOutgoingAddress(psstate->request, p);
            psstate->paths->push_back(p);
        }
    } else {
        debugs(44, 3, HERE << "Unknown host: " << (fs->_peer ? fs->_peer->host : psstate->request->GetHost()));
        // discard any previous error.
        delete psstate->lastError;
        psstate->lastError = NULL;
        if (fs->code == HIER_DIRECT) {
            psstate->lastError = new ErrorState(ERR_DNS_FAIL, Http::scServiceUnavailable, psstate->request);
            psstate->lastError->dnsError = details.error;
        }
    }

    psstate->servers = fs->next;
    cbdataReferenceDone(fs->_peer);
    delete fs;

    // see if more paths can be found
    peerSelectDnsPaths(psstate);
}