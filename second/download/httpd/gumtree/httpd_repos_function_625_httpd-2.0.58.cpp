static unsigned char *entry_data_buf(const table_t * table_p,
                                     const table_entry_t * entry_p)
{
    const unsigned char *buf_p;
    int size, pad;

    buf_p = entry_p->te_key_buf + entry_p->te_key_size;

    /* if there is no alignment then it is easy */
    if (table_p->ta_data_align == 0)
        return (unsigned char *) buf_p;
    /* we need the size of the space before the data */
    size = sizeof(struct table_shell_st) + entry_p->te_key_size;

    /* add in our alignment */
    pad = size & (table_p->ta_data_align - 1);
    if (pad > 0)
        pad = table_p->ta_data_align - pad;
    return (unsigned char *) buf_p + pad;
}