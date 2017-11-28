void
StoreEntry::createMemObject(const char *aUrl, const char *aLogUrl)
{
    if (mem_obj)
        return;

    mem_obj = new MemObject(aUrl, aLogUrl);
}