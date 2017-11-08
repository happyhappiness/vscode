table_entry_t **table_order(table_t * table_p, table_compare_t compare,
                            int *num_entries_p, int *error_p)
{
    table_entry_t *entry_p, **entries, **entries_p;
    table_linear_t linear;
    compare_t comp_func;
    int error;

    if (table_p == NULL) {
        if (error_p != NULL)
            *error_p = TABLE_ERROR_ARG_NULL;
        return NULL;
    }
    if (table_p->ta_magic != TABLE_MAGIC) {
        if (error_p != NULL)
            *error_p = TABLE_ERROR_PNT;
        return NULL;
    }

    /* there must be at least 1 element in the table for this to work */
    if (table_p->ta_entry_n == 0) {
        if (error_p != NULL)
            *error_p = TABLE_ERROR_EMPTY;
        return NULL;
    }

    entries = (table_entry_t **)
               table_p->ta_malloc(table_p->opt_param,
                                  table_p->ta_entry_n *sizeof(table_entry_t *));
    if (entries == NULL) {
        if (error_p != NULL)
            *error_p = TABLE_ERROR_ALLOC;
        return NULL;
    }

    /* get a pointer to all entries */
    entry_p = first_entry(table_p, &linear);
    if (entry_p == NULL) {
        if (error_p != NULL)
            *error_p = TABLE_ERROR_NOT_FOUND;
        return NULL;
    }

    /* add all of the entries to the array */
    for (entries_p = entries;
         entry_p != NULL;
         entry_p = next_entry(table_p, &linear, &error))
        *entries_p++ = entry_p;
    if (error != TABLE_ERROR_NOT_FOUND) {
        if (error_p != NULL)
            *error_p = error;
        return NULL;
    }

    if (compare == NULL) {
        /* this is regardless of the alignment */
        comp_func = local_compare;
    }
    else if (table_p->ta_data_align == 0)
        comp_func = external_compare;
    else
        comp_func = external_compare_align;
    /* now qsort the entire entries array from first to last element */
    split(entries, entries + table_p->ta_entry_n - 1, comp_func, compare,
          table_p);

    if (num_entries_p != NULL)
        *num_entries_p = table_p->ta_entry_n;
    if (error_p != NULL)
        *error_p = TABLE_ERROR_NONE;
    return entries;
}