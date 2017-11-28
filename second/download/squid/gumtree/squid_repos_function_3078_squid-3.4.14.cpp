int64_t
StoreEntry::objectLen() const
{
    assert(mem_obj != NULL);
    return mem_obj->object_sz;
}