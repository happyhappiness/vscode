int
Ipc::StoreMap::entryLimit() const
{
    return min(sliceLimit(), static_cast<int>(SwapFilenMax+1));
}