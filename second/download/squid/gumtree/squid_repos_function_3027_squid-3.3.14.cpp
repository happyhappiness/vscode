void
StoreEntry::createMemObject(const char *aUrl, const char *aLogUrl)
{
    if (mem_obj)
        return;

    if (hidden_mem_obj) {
        debugs(20, 3, HERE << "restoring " << hidden_mem_obj);
        mem_obj = hidden_mem_obj;
        hidden_mem_obj = NULL;
        mem_obj->resetUrls(aUrl, aLogUrl);
        return;
    }

    mem_obj = new MemObject(aUrl, aLogUrl);
}