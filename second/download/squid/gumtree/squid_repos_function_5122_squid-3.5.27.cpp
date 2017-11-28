bool
Rock::SwapDir::updateCollapsedWith(StoreEntry &collapsed, const Ipc::StoreMapAnchor &anchor)
{
    collapsed.swap_file_sz = anchor.basics.swap_file_sz;
    return true;
}