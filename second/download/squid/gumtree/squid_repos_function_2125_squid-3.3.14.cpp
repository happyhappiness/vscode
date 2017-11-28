bool
mem_hdr::unionNotEmpty(StoreIOBuffer const &candidate)
{
    assert (candidate.offset >= 0);
    mem_node target(candidate.offset);
    target.nodeBuffer.length = candidate.length;
    return nodes.find (&target, NodeCompare);
}