heap_t
heap_update(heap * hp, heap_node * elm, void *dat)
{
    heap_t old = elm->data;
    heap_key ky = heap_gen_key(hp, dat);

    elm->key = ky;
    elm->data = dat;

    if (elm->key < hp->nodes[Parent(elm->id)]->key)
        _heap_ify_up(hp, elm);
    _heap_ify_down(hp, elm);

    return old;
}