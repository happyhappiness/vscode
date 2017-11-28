void
mem_hdr::freeContent()
{
    nodes.destroy(SplayNode<mem_node *>::DefaultFree);
    inmem_hi = 0;
}