static void
peerPingTimeout(void *data)
{
    ps_state *psstate = (ps_state *)data;
    StoreEntry *entry = psstate->entry;

    if (entry)
        debugs(44, 3, "peerPingTimeout: '" << entry->url() << "'" );

    if (!cbdataReferenceValid(psstate->callback_data)) {
        /* request aborted */
        entry->ping_status = PING_DONE;
        cbdataReferenceDone(psstate->callback_data);
        peerSelectStateFree(psstate);
        return;
    }

    PeerStats.timeouts++;
    psstate->ping.timedout = 1;
    peerSelectFoo(psstate);
}