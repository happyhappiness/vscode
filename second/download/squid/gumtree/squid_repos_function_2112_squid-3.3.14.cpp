void
mem_hdr::freeContent()
{
    nodes.destroy(SplayNode<mem_node *>::DefaultFree);
    inmem_hi = 0;
    debugs(19, 9, HERE << this << " hi: " << inmem_hi);
}