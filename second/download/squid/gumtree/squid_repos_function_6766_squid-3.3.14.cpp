heap_t
heap_extractlast(heap * hp)
{
    heap_t data;
    assert(_heap_node_exist(hp, hp->last - 1));
    hp->last -= 1;
    data = hp->nodes[hp->last]->data;
    xfree(hp->nodes[hp->last]);
    return data;
}