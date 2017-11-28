const Ipc::StoreMap::Anchor&
Ipc::StoreMap::anchorAt(const sfileno fileno) const
{
    return const_cast<StoreMap&>(*this).anchorAt(fileno);
}