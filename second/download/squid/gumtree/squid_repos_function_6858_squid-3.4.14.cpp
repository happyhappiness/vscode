static int
_heap_node_exist(heap * hp, int id)
{
    if ((id >= hp->last) || (id < 0) || (hp->nodes[id] == NULL))
        return 0;
    return 1;
}