int64_t
Rock::SwapDir::diskOffset(int filen) const
{
    assert(filen >= 0);
    return HeaderSize + max_objsize*filen;
}