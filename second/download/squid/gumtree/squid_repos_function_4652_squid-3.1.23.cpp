void
UFSSwapDir::mapBitReset(sfileno filn)
{
    /*
     * We have to test the bit before calling file_map_bit_reset.
     * file_map_bit_reset doesn't do bounds checking.  It assumes
     * filn is a valid file number, but it might not be because
     * the map is dynamic in size.  Also clearing an already clear
     * bit puts the map counter of-of-whack.
     */

    if (file_map_bit_test(map, filn))
        file_map_bit_reset(map, filn);
}