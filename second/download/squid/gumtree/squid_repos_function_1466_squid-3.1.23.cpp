void
file_map_bit_reset(fileMap * fm, int file_number)
{
    unsigned long bitmask = (1L << (file_number & LONG_BIT_MASK));
    fm->file_map[file_number >> LONG_BIT_SHIFT] &= ~bitmask;
    fm->n_files_in_map--;
}