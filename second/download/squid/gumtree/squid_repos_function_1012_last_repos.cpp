static void
peerPingTimeout(void *data)
{
    ps_state *psstate = (ps_state *)data;
    StoreEntry *entry = psstate->entry;

    if (entry)
        debugs(44, 3, psstate->url());

    if (!cbdataReferenceValid(psstate->callback_data)) {
        /* request aborted */
        if (entry)
            entry->ping_status = PING_DONE;
        cbdataReferenceDone(psstate->callback_data);
        delete psstate;
        return;
    }

    ++PeerStats.timeouts;
    psstate->ping.timedout = 1;
    peerSelectFoo(psstate);
}