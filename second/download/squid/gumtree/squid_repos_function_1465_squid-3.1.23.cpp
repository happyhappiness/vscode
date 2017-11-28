int
file_map_bit_set(fileMap * fm, int file_number)
{
    unsigned long bitmask = (1L << (file_number & LONG_BIT_MASK));

    while (file_number >= fm->max_n_files)
        file_map_grow(fm);

    fm->file_map[file_number >> LONG_BIT_SHIFT] |= bitmask;

    fm->n_files_in_map++;

    return file_number;
}