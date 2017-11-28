void
peerSelect(Comm::ConnectionList * paths,
           HttpRequest * request,
           StoreEntry * entry,
           PSC * callback,
           void *callback_data)
{
    ps_state *psstate;

    if (entry)
        debugs(44, 3, "peerSelect: " << entry->url()  );
    else
        debugs(44, 3, "peerSelect: " << RequestMethodStr(request->method));

    psstate = new ps_state;

    psstate->request = HTTPMSGLOCK(request);

    psstate->entry = entry;
    psstate->paths = paths;

    psstate->callback = callback;

    psstate->callback_data = cbdataReference(callback_data);

#if USE_CACHE_DIGESTS

    request->hier.peer_select_start = current_time;

#endif

    if (psstate->entry)
        psstate->entry->lock();

    peerSelectFoo(psstate);
}