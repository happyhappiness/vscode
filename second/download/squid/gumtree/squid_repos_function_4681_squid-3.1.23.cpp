void
UFSSwapDir::unlink(StoreEntry & e)
{
    debugs(79, 3, "storeUfsUnlink: dirno " << index  << ", fileno "<<
           std::setfill('0') << std::hex << std::uppercase << std::setw(8) << e.swap_filen);
    replacementRemove(&e);
    mapBitReset(e.swap_filen);
    UFSSwapDir::unlinkFile(e.swap_filen);
}