void
StoreSwapLogData::finalize()
{
    checksum.set(swap_filen, swap_file_sz);
}