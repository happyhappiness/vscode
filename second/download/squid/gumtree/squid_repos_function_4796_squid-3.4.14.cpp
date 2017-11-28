int64_t
MemObject::endOffset() const
{
    // XXX: required by testStore
    return data_hdr.endOffset();
}