static ptrdiff_t
makeMemNodeDataOffset()
{
    mem_node *p = 0L;
    return ptrdiff_t(&p->data);
}