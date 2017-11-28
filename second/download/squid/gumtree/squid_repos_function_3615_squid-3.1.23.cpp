static void
urnHandleReplyError(UrnState *urnState, StoreEntry *urlres_e)
{
    urlres_e->unlock();
    urnState->entry->unlock();
    HTTPMSGUNLOCK(urnState->request);
    HTTPMSGUNLOCK(urnState->urlres_r);
    delete urnState;
}