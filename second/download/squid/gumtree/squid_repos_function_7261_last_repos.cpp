void
Mgr::FunAction::dump(StoreEntry* entry)
{
    debugs(16, 5, HERE);
    Must(entry != NULL);
    if (UsingSmp())
        storeAppendPrintf(entry, "by kid%d {\n", KidIdentifier);
    handler(entry);
    if (atomic() && UsingSmp())
        storeAppendPrintf(entry, "} by kid%d\n\n", KidIdentifier);
}