cache_cache_t* cache_init(int max_entries,
                                         apr_size_t max_size,
                                         cache_pqueue_get_priority get_pri,
                                         cache_pqueue_set_priority set_pri,
                                         cache_pqueue_getpos get_pos,
                                         cache_pqueue_setpos set_pos,
                                         cache_cache_inc_frequency *inc_entry,
                                         cache_cache_get_size *size_entry,
                                         cache_cache_get_key* key_entry,
                                         cache_cache_free *free_entry)
{
    cache_cache_t *tmp;
    tmp = malloc(sizeof(cache_cache_t));
    tmp->max_entries = max_entries;
    tmp->max_size = max_size;
    tmp->current_size = 0;
    tmp->total_purges = 0;
    tmp->queue_clock = 0;
    tmp->get_pri = get_pri;
    tmp->set_pri = set_pri;
    tmp->inc_entry = inc_entry;
    tmp->size_entry = size_entry;
    tmp->key_entry = key_entry;
    tmp->free_entry = free_entry;

    tmp->ht = cache_hash_make(max_entries);
    tmp->pq = cache_pq_init(max_entries, get_pri, get_pos, set_pos);

    return tmp;
}