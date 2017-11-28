static void
peerSelectCallback(ps_state * psstate)
{
    StoreEntry *entry = psstate->entry;
    FwdServer *fs = psstate->servers;
    PSC *callback;
    void *cbdata;

    if (entry) {
        debugs(44, 3, "peerSelectCallback: " << entry->url()  );

        if (entry->ping_status == PING_WAITING)
            eventDelete(peerPingTimeout, psstate);

        entry->ping_status = PING_DONE;
    }

    if (fs == NULL) {
        debugs(44, 1, "Failed to select source for '" << entry->url() << "'" );
        debugs(44, 1, "  always_direct = " << psstate->always_direct  );
        debugs(44, 1, "   never_direct = " << psstate->never_direct  );
        debugs(44, 1, "       timedout = " << psstate->ping.timedout  );
    }

    psstate->ping.stop = current_time;
    psstate->request->hier.ping = psstate->ping;
    callback = psstate->callback;
    psstate->callback = NULL;

    if (cbdataReferenceValidDone(psstate->callback_data, &cbdata)) {
        psstate->servers = NULL;
        callback(fs, cbdata);
    }

    peerSelectStateFree(psstate);
}