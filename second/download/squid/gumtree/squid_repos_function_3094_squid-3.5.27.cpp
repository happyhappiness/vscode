void
StoreEntry::createMemObject(const char *aUrl, const char *aLogUrl, const HttpRequestMethod &aMethod)
{
    makeMemObject();
    mem_obj->setUris(aUrl, aLogUrl, aMethod);
}