heap_node *
heap_insert(heap * hp, void *dat)
{
    heap_node *elm = xmalloc(sizeof(*elm));

    elm->key = heap_gen_key(hp, dat);
    elm->data = dat;

    if (_heap_should_grow(hp))
        _heap_grow(hp);

    hp->nodes[hp->last] = elm;
    elm->id = hp->last;
    hp->last += 1;

    _heap_ify_up(hp, elm);

    return elm;
}