const MemBuf &
Helper::Reply::emptyBuf() const
{
    static MemBuf empty;
    if (empty.isNull())
        empty.init(1, 1);
    return empty;
}