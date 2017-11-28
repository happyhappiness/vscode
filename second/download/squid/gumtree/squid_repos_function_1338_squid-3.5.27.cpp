void
peerSelect(Comm::ConnectionList * paths,
           HttpRequest * request,
           AccessLogEntry::Pointer const &al,
           StoreEntry * entry,
           PSC * callback,
           void *callback_data)
{
    ps_state *psstate;

    if (entry)
        debugs(44, 3, *entry << ' ' << entry->url());
    else
        debugs(44, 3, request->method);

    psstate = new ps_state;

    psstate->request = request;
    HTTPMSGLOCK(psstate->request);
    psstate->al = al;

    psstate->entry = entry;
    psstate->paths = paths;

    psstate->callback = callback;

    psstate->callback_data = cbdataReference(callback_data);

#if USE_CACHE_DIGESTS

    request->hier.peer_select_start = current_time;

#endif

    if (psstate->entry)
        psstate->entry->lock("peerSelect");

    peerSelectFoo(psstate);
}