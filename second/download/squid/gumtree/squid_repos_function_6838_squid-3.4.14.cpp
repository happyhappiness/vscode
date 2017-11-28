heap *
new_heap(int initSize, heap_key_func gen_key)
{
    heap *hp = xmalloc(sizeof(*hp));
    assert(hp != NULL);

    if (initSize <= 0)
        initSize = MinSize;
    hp->nodes = xcalloc(initSize, sizeof(heap_node *));
    assert(hp->nodes != NULL);

    hp->size = initSize;
    hp->last = 0;
    hp->gen_key = gen_key;
    hp->age = 0;

    return hp;
}