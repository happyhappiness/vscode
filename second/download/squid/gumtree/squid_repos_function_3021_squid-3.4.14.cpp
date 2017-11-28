void
StoreEntry::destroyMemObject()
{
    debugs(20, 3, HERE << "destroyMemObject " << mem_obj);
    setMemStatus(NOT_IN_MEMORY);
    MemObject *mem = mem_obj;
    mem_obj = NULL;
    delete mem;
    delete hidden_mem_obj;
    hidden_mem_obj = NULL;
}