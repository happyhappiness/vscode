void
StoreEntry::storeErrorResponse(HttpReply *reply)
{
    lock("StoreEntry::storeErrorResponse");
    buffer();
    replaceHttpReply(reply);
    flush();
    complete();
    negativeCache();
    releaseRequest();
    unlock("StoreEntry::storeErrorResponse");
}