static int local_compare(const void *p1, const void *p2,
                         table_compare_t compare, const table_t * table_p)
{
    const table_entry_t *const *ent1_p = p1, *const *ent2_p = p2;
    int cmp;
    unsigned int size;

    /* compare as many bytes as we can */
    size = (*ent1_p)->te_key_size;
    if ((*ent2_p)->te_key_size < size)
        size = (*ent2_p)->te_key_size;
    cmp = memcmp(ENTRY_KEY_BUF(*ent1_p), ENTRY_KEY_BUF(*ent2_p), size);
    /* if common-size equal, then if next more bytes, it is larger */
    if (cmp == 0)
        cmp = (*ent1_p)->te_key_size - (*ent2_p)->te_key_size;
    return cmp;
}