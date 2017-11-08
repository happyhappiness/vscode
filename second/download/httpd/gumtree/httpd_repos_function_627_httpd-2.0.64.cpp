static int entry_size(const table_t * table_p, const unsigned int key_size,
                      const unsigned int data_size)
{
    int size, left;

    /* initial size -- key is already aligned if right after struct */
    size = sizeof(struct table_shell_st) + key_size;

    /* if there is no alignment then it is easy */
    if (table_p->ta_data_align == 0)
        return size + data_size;
    /* add in our alignement */
    left = size & (table_p->ta_data_align - 1);
    if (left > 0)
        size += table_p->ta_data_align - left;
    /* we add the data size here after the alignment */
    size += data_size;

    return size;
}