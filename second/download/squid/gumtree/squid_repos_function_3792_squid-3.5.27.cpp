static void
urnHandleReplyError(UrnState *urnState, StoreEntry *urlres_e)
{
    urlres_e->unlock("urnHandleReplyError+res");
    urnState->entry->unlock("urnHandleReplyError+prime");
    delete urnState;
}