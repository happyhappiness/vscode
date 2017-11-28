bool
Store::Disks::updateCollapsed(StoreEntry &collapsed)
{
    return collapsed.swap_filen >= 0 &&
           dir(collapsed.swap_dirn).updateCollapsed(collapsed);
}