heap_key
heap_peepkey(heap * hp, int n)
{
    assert(_heap_node_exist(hp, n));
    return hp->nodes[n]->key;
}