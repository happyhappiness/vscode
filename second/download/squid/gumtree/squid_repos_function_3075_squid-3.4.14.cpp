void
StoreEntry::createMemObject(const char *aUrl, const char *aLogUrl)
{
    debugs(20, 3, "A mem_obj create attempted using : " << aUrl);

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