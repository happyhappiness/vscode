void
clientReplyContext::purgeDoMissPurge()
{
    http->logType = LOG_TCP_MISS;
    lookingforstore = 3;
    StoreEntry::getPublicByRequestMethod(this,http->request, Http::METHOD_GET);
}