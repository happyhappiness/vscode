void
StoreEntry::unregisterAbort()
{
    assert(mem_obj);
    if (mem_obj->abort.callback) {
        mem_obj->abort.callback = NULL;
        cbdataReferenceDone(mem_obj->abort.data);
    }
}