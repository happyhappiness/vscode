static void expand_array(apr_hash_t *ht)
{
    apr_hash_index_t *hi;
    apr_hash_entry_t **new_array;
    unsigned int new_max;

    new_max = ht->max * 2 + 1;
    new_array = alloc_array(ht, new_max);
    for (hi = apr_hash_first(NULL, ht); hi; hi = apr_hash_next(hi)) {
        unsigned int i = hi->this->hash & new_max;
        hi->this->next = new_array[i];
        new_array[i] = hi->this;
    }
    ht->array = new_array;
    ht->max = new_max;
}