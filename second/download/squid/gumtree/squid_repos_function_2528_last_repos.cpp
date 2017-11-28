MemObject *
StoreEntry::makeMemObject()
{
    if (!mem_obj)
        mem_obj = new MemObject();
    return mem_obj;
}