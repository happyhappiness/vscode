const Ipc::StoreMap::Anchor &
Ipc::StoreMap::readableEntry(const AnchorId anchorId) const
{
    assert(anchorAt(anchorId).reading());
    return anchorAt(anchorId);
}