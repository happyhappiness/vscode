void cache_update(cache_cache_t* c, void *entry)
{
    long old_priority;
    long new_priority;

    old_priority = c->set_pri(c->queue_clock, entry);
    c->inc_entry(entry);
    new_priority = c->set_pri(c->queue_clock, entry);
    cache_pq_change_priority(c->pq, old_priority, new_priority, entry);
}