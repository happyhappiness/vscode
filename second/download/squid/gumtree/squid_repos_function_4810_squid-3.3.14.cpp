uint64_t
Rock::SwapDir::currentSize() const
{
    return HeaderSize + max_objsize * currentCount();
}