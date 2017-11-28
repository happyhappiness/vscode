void
clientReplyContext::purgeRequestFindObjectToPurge()
{
    /* Try to find a base entry */
    http->flags.purging = 1;
    lookingforstore = 1;

    // TODO: can we use purgeAllCached() here instead of doing the
    // getPublicByRequestMethod() dance?
    StoreEntry::getPublicByRequestMethod(this, http->request, METHOD_GET);
}