size_t
Ipc::StoreMapAnchors::SharedMemorySize(const int capacity)
{
    return sizeof(StoreMapAnchors) + capacity * sizeof(StoreMapAnchor);
}