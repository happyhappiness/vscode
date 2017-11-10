static int external_compare(const void *p1, const void *p2,
                            table_compare_t user_compare,
                            const table_t * table_p)
{
    const table_entry_t *const *ent1_p = p1, *const *ent2_p = p2;
    /* since we know we are not aligned we can use the EXTRY_DATA_BUF macro */
    return user_compare(ENTRY_KEY_BUF(*ent1_p), (*ent1_p)->te_key_size,
                        ENTRY_DATA_BUF(table_p, *ent1_p),
                        (*ent1_p)->te_data_size,
                        ENTRY_KEY_BUF(*ent2_p), (*ent2_p)->te_key_size,
                        ENTRY_DATA_BUF(table_p, *ent2_p),
                        (*ent2_p)->te_data_size);
}