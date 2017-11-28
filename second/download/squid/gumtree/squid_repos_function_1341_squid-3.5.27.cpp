void
peerSelectDnsPaths(ps_state *psstate)
{
    FwdServer *fs = psstate->servers;

    if (!cbdataReferenceValid(psstate->callback_data)) {
        debugs(44, 3, "Aborting peer selection. Parent Job went away.");
        delete psstate;
        return;
    }

    // Bug 3243: CVE 2009-0801
    // Bypass of browser same-origin access control in intercepted communication
    // To resolve this we must use only the original client destination when going DIRECT
    // on intercepted traffic which failed Host verification
    const HttpRequest *req = psstate->request;
    const bool isIntercepted = !req->flags.redirected &&
                               (req->flags.intercepted || req->flags.interceptTproxy);
    const bool useOriginalDst = Config.onoff.client_dst_passthru || !req->flags.hostVerified;
    const bool choseDirect = fs && fs->code == HIER_DIRECT;
    if (isIntercepted && useOriginalDst && choseDirect) {
        // check the client is still around before using any of its details
        if (req->clientConnectionManager.valid()) {
            // construct a "result" adding the ORIGINAL_DST to the set instead of DIRECT
            Comm::ConnectionPointer p = new Comm::Connection();
            p->remote = req->clientConnectionManager->clientConnection->local;
            p->peerType = ORIGINAL_DST; // fs->code is DIRECT. This fixes the display.
            p->setPeer(fs->_peer);

            // check for a configured outgoing address for this destination...
            getOutgoingAddress(psstate->request, p);
            psstate->paths->push_back(p);
        }

        // clear the used fs and continue
        psstate->servers = fs->next;
        cbdataReferenceDone(fs->_peer);
        delete fs;
        peerSelectDnsPaths(psstate);
        return;
    }

    // convert the list of FwdServer destinations into destinations IP addresses
    if (fs && psstate->paths->size() < (unsigned int)Config.forward_max_tries) {
        // send the next one off for DNS lookup.
        const char *host = fs->_peer ? fs->_peer->host : psstate->request->GetHost();
        debugs(44, 2, "Find IP destination for: " << psstate->url() << "' via " << host);
        ipcache_nbgethostbyname(host, peerSelectDnsResults, psstate);
        return;
    }

    // Bug 3605: clear any extra listed FwdServer destinations, when the options exceeds max_foward_tries.
    // due to the allocation method of fs, we must deallocate each manually.
    // TODO: use a std::list so we can get the size and abort adding whenever the selection loops reach Config.forward_max_tries
    if (fs && psstate->paths->size() >= (unsigned int)Config.forward_max_tries) {
        assert(fs == psstate->servers);
        while (fs) {
            psstate->servers = fs->next;
            cbdataReferenceDone(fs->_peer);
            delete fs;
            fs = psstate->servers;
        }
    }

    // done with DNS lookups. pass back to caller
    PSC *callback = psstate->callback;
    psstate->callback = NULL;

    debugs(44, 2, (psstate->paths->size()<1?"Failed to select source":"Found sources") << " for '" << psstate->url() << "'");
    debugs(44, 2, "  always_direct = " << psstate->always_direct);
    debugs(44, 2, "   never_direct = " << psstate->never_direct);
    if (psstate->paths) {
        for (size_t i = 0; i < psstate->paths->size(); ++i) {
            if ((*psstate->paths)[i]->peerType == HIER_DIRECT)
                debugs(44, 2, "         DIRECT = " << (*psstate->paths)[i]);
            else if ((*psstate->paths)[i]->peerType == ORIGINAL_DST)
                debugs(44, 2, "   ORIGINAL_DST = " << (*psstate->paths)[i]);
            else if ((*psstate->paths)[i]->peerType == PINNED)
                debugs(44, 2, "         PINNED = " << (*psstate->paths)[i]);
            else
                debugs(44, 2, "     cache_peer = " << (*psstate->paths)[i]);
        }
    }
    debugs(44, 2, "       timedout = " << psstate->ping.timedout);

    psstate->ping.stop = current_time;
    psstate->request->hier.ping = psstate->ping;

    void *cbdata;
    if (cbdataReferenceValidDone(psstate->callback_data, &cbdata)) {
        callback(psstate->paths, psstate->lastError, cbdata);
        psstate->lastError = NULL; // FwdState has taken control over the ErrorState object.
    }

    delete psstate;
}