int
file_map_allocate(fileMap * fm, int suggestion)
{
    int word;
    int bit;
    int count;

    if (suggestion >= fm->max_n_files)
        suggestion = 0;

    if (!file_map_bit_test(fm, suggestion))
        return suggestion;

    word = suggestion >> LONG_BIT_SHIFT;

    for (count = 0; count < fm->nwords; count++) {
        if (fm->file_map[word] != ALL_ONES)
            break;

        word = (word + 1) % fm->nwords;
    }

    for (bit = 0; bit < BITS_IN_A_LONG; bit++) {
        suggestion = ((unsigned long) word << LONG_BIT_SHIFT) | bit;

        if (!file_map_bit_test(fm, suggestion)) {
            return suggestion;
        }
    }

    debugs(8, 3, "growing from file_map_allocate");
    file_map_grow(fm);
    return file_map_allocate(fm, fm->max_n_files >> 1);
}