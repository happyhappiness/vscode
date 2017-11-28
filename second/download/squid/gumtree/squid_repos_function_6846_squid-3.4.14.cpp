void *
heap_peepmin(heap * hp)
{
    assert(_heap_node_exist(hp, 0));
    return hp->nodes[0]->data;
}