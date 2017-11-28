static void
gopherStateFree(int fdnotused, void *data)
{
    GopherStateData *gopherState = (GopherStateData *)data;

    if (gopherState == NULL)
        return;

    if (gopherState->entry) {
        gopherState->entry->unlock();
    }

    HTTPMSGUNLOCK(gopherState->req);

    gopherState->fwd = NULL;	// refcounted

    memFree(gopherState->buf, MEM_4K_BUF);
    gopherState->buf = NULL;
    cbdataFree(gopherState);
}