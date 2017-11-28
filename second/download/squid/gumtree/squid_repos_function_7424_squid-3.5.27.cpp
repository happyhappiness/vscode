int
heap_empty(heap * hp)
{
    return (hp->last <= 0) ? 1 : 0;
}