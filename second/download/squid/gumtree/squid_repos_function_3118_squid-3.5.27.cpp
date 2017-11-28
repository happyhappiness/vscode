void
StoreEntry::unlink()
{
    store()->unlink(*this); // implies disconnect()
    swap_filen = -1;
    swap_dirn = -1;
    swap_status = SWAPOUT_NONE;
}