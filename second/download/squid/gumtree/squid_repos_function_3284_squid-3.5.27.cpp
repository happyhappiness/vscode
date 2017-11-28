bool
MemStore::updateCollapsedWith(StoreEntry &collapsed, const sfileno index, const Ipc::StoreMapAnchor &anchor)
{
    collapsed.swap_file_sz = anchor.basics.swap_file_sz;
    const bool copied = copyFromShm(collapsed, index, anchor);
    return copied;
}