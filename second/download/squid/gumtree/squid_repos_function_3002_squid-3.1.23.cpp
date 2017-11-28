int64_t
StoreEntry::contentLen() const
{
    assert(mem_obj != NULL);
    assert(getReply() != NULL);
    return objectLen() - getReply()->hdr_sz;
}