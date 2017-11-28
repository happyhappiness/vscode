Ipc::StoreMap::Owner *
Ipc::StoreMap::Init(const SBuf &path, const int sliceLimit)
{
    assert(sliceLimit > 0); // we should not be created otherwise
    const int anchorLimit = min(sliceLimit, static_cast<int>(SwapFilenMax));
    Owner *owner = new Owner;
    owner->anchors = shm_new(Anchors)(StoreMapAnchorsId(path).c_str(), anchorLimit);
    owner->slices = shm_new(Slices)(StoreMapSlicesId(path).c_str(), sliceLimit);
    debugs(54, 5, "created " << path << " with " << anchorLimit << '+' << sliceLimit);
    return owner;
}