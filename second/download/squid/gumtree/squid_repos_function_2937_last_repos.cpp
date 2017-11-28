void
clientReplyContext::identifyStoreObject()
{
    HttpRequest *r = http->request;

    // client sent CC:no-cache or some other condition has been
    // encountered which prevents delivering a public/cached object.
    if (!r->flags.noCache || r->flags.internal) {
        lookingforstore = 5;
        StoreEntry::getPublicByRequest (this, r);
    } else {
        identifyFoundObject (NullStoreEntry::getInstance());
    }
}