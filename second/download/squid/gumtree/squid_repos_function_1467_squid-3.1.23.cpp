int
file_map_bit_test(fileMap * fm, int file_number)
{
    unsigned long bitmask = (1L << (file_number & LONG_BIT_MASK));

    if (file_number >= fm->max_n_files)
        return 0;

    /* be sure the return value is an int, not a u_long */
    return (fm->file_map[file_number >> LONG_BIT_SHIFT] & bitmask ? 1 : 0);
}