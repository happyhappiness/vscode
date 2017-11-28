Ipc::StoreMap::Anchor &
Ipc::StoreMap::writeableEntry(const AnchorId anchorId)
{
    assert(anchorAt(anchorId).writing());
    return anchorAt(anchorId);
}