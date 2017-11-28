void
clientReplyContext::identifyStoreObject()
{
    HttpRequest *r = http->request;

    if (r->flags.cachable || r->flags.internal) {
        lookingforstore = 5;
        StoreEntry::getPublicByRequest (this, r);
    } else {
        identifyFoundObject (NullStoreEntry::getInstance());
    }
}