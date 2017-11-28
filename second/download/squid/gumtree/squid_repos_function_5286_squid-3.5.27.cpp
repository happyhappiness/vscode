void
Fs::Ufs::UFSSwapDir::mapBitReset(sfileno filn)
{
    /*
     * We have to test the bit before calling clearBit as
     * it doesn't do bounds checking and blindly assumes
     * filn is a valid file number, but it might not be because
     * the map is dynamic in size.  Also clearing an already clear
     * bit puts the map counter of-of-whack.
     */

    if (map->testBit(filn))
        map->clearBit(filn);
}