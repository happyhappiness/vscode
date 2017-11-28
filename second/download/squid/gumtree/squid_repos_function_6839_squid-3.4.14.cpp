void
delete_heap(heap * hp)
{
    int i;
    assert(hp != NULL);
    for (i = 0; i < hp->last; i++) {
        xfree(hp->nodes[i]);
    }
    xfree(hp->nodes);
    xfree(hp);
}