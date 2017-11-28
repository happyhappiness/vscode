void
StoreEntry::hideMemObject()
{
    debugs(20, 3, HERE << "hiding " << mem_obj);
    assert(mem_obj);
    assert(!hidden_mem_obj);
    hidden_mem_obj = mem_obj;
    mem_obj = NULL;
}