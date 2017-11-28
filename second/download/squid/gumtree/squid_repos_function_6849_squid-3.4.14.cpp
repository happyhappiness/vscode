void *
heap_peep(heap * hp, int n)
{
    void *data;
    assert(_heap_node_exist(hp, n));
    data = hp->nodes[n]->data;
    return data;
}