void
clientReplyContext::purgeFoundGet(StoreEntry *newEntry)
{
    if (newEntry->isNull()) {
        lookingforstore = 2;
        StoreEntry::getPublicByRequestMethod(this, http->request, Http::METHOD_HEAD);
    } else
        purgeFoundObject (newEntry);
}