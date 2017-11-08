int table_free(table_t * table_p)
{
    int ret;

    if (table_p == NULL)
        return TABLE_ERROR_ARG_NULL;
    if (table_p->ta_magic != TABLE_MAGIC)
        return TABLE_ERROR_PNT;
    ret = table_clear(table_p);

    if (table_p->ta_buckets != NULL)
        table_p->ta_free(table_p->opt_param, table_p->ta_buckets);
    table_p->ta_magic = 0;
    table_p->ta_free(table_p->opt_param, table_p);

    return ret;
}