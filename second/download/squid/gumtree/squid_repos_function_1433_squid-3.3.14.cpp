bool
StoreSwapLogData::sane() const
{
    SwapChecksum24 actualSum;
    actualSum.set(swap_filen, swap_file_sz);
    if (checksum != actualSum)
        return false;

    const time_t minTime = -2; // -1 is common; expires sometimes uses -2

    // Check what we safely can; for some fields any value might be valid
    return SWAP_LOG_NOP < op && op < SWAP_LOG_MAX &&
           swap_filen >= 0 &&
           timestamp >= minTime &&
           lastref >= minTime &&
           expires >= minTime &&
           lastmod >= minTime &&
           swap_file_sz > 0; // because swap headers ought to consume space
}