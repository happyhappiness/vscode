void
StoreEntry::invokeHandlers()
{
    /* Commit what we can to disk, if appropriate */
    swapOut();
    int i = 0;
    store_client *sc;
    dlink_node *nx = NULL;
    dlink_node *node;

    PROF_start(InvokeHandlers);

    debugs(90, 3, "InvokeHandlers: " << getMD5Text()  );
    /* walk the entire list looking for valid callbacks */

    for (node = mem_obj->clients.head; node; node = nx) {
        sc = (store_client *)node->data;
        nx = node->next;
        debugs(90, 3, "StoreEntry::InvokeHandlers: checking client #" << i  );
        ++i;

        if (!sc->_callback.pending())
            continue;

        if (sc->flags.disk_io_pending)
            continue;

        storeClientCopy2(this, sc);
    }
    PROF_stop(InvokeHandlers);
}