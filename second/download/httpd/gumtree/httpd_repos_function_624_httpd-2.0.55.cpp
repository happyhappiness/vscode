int table_attr(table_t * table_p, const int attr)
{
    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    table_p->ta_flags = attr;

    return TABLE_ERROR_NONE;
}