const Ipc::StoreMap::Anchor &
Ipc::StoreMap::peekAtEntry(const sfileno fileno) const
{
    return anchorAt(fileno);
}