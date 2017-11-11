void cache_pq_print(cache_pqueue_t *q,
                    FILE*out,
                    cache_pqueue_print_entry print)
{
    cache_pqueue_t *dup;
    dup = cache_pq_init(q->size, q->pri, q->get, cache_pq_set_null);
    dup->size = q->size;
    dup->avail = q->avail;
    dup->step = q->step;

    memcpy(dup->d, q->d, q->size*sizeof(void*));

    while (cache_pq_size(dup) > 1) {
        void *e = NULL;
        e = cache_pq_pop(dup);
        if (e)
            print(out, e);
        else
            break;
    }
    cache_pq_free(dup);
}