static int
_heap_should_grow(heap * hp)
{
    if (hp->size <= hp->last)
        return 1;
    return 0;
}