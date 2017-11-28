Ipc::StoreMap::Anchor&
Ipc::StoreMap::anchorAt(const sfileno fileno)
{
    assert(validEntry(fileno));
    return anchors->items[fileno];
}