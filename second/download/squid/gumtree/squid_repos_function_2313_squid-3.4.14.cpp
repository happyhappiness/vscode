int64_t
MemObject::size() const
{
    if (object_sz < 0)
        return endOffset();

    return object_sz;
}