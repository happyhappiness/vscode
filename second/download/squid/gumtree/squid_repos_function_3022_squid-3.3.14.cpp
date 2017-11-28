void
StoreEntry::registerAbort(STABH * cb, void *data)
{
    assert(mem_obj);
    assert(mem_obj->abort.callback == NULL);
    mem_obj->abort.callback = cb;
    mem_obj->abort.data = cbdataReference(data);
}