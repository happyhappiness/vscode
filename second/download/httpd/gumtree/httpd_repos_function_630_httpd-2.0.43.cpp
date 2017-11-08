int table_set_data_alignment(table_t * table_p, const int alignment)
{
    int val;

    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    if (table_p->ta_entry_n > 0)
        return TABLE_ERROR_NOT_EMPTY;
    /* defaults */
    if (alignment < 2)
        table_p->ta_data_align = 0;
    else {
        /* verify we have a base 2 number */
        for (val = 2; val < MAX_ALIGNMENT; val *= 2) {
            if (val == alignment)
                break;
        }
        if (val >= MAX_ALIGNMENT)
            return TABLE_ERROR_ALIGNMENT;
        table_p->ta_data_align = alignment;
    }

    return TABLE_ERROR_NONE;
}