static void
urnHandleReplyError(UrnState *urnState, StoreEntry *urlres_e)
{
    urlres_e->unlock();
    urnState->entry->unlock();
    delete urnState;
}