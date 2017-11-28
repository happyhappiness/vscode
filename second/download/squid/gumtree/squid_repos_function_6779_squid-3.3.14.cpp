static void
_heap_grow(heap * hp)
{
    int newSize;

    if (hp->size > Threshold)
        newSize = hp->size * SlowRate;
    else
        newSize = hp->size * NormalRate;

    hp->nodes = xrealloc(hp->nodes, newSize * sizeof(heap_node *));
#if COMMENTED_OUT
    for (i = 0; i < hp->size; i++)
        newNodes[i] = hp->nodes[i];
    xfree(hp->nodes);
    hp->nodes = newNodes;
#endif
    hp->size = newSize;
}