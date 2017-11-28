heap_t
heap_extractmin(heap * hp)
{
    heap_t data;

    if (hp->last <= 0)
        return NULL;

    mutex_lock(hp->lock);

    data = hp->nodes[0]->data;
    heap_delete(hp, hp->nodes[0]);	/* Delete the root */

    mutex_unlock(hp->lock);

    return data;
}