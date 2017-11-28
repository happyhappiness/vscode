SwapDir &
StoreHashIndex::dir(const int i) const
{
    SwapDir *sd = dynamic_cast<SwapDir*>(INDEXSD(i));
    assert(sd);
    return *sd;
}