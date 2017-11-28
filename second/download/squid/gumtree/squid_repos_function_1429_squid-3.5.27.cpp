MemBlob::Pointer
SBuf::GetStorePrototype()
{
    static MemBlob::Pointer InitialStore = new MemBlob(0);
    return InitialStore;
}