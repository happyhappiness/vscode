const Ipc::StoreMapSlice &
Rock::IoState::currentReadableSlice() const
{
    return dir->map->readableSlice(swap_filen, sidCurrent);
}