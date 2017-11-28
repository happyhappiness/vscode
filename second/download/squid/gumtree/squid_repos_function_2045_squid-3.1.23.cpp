void
mem_hdr::appendNode (mem_node *aNode)
{
    nodes.insert (aNode, NodeCompare);
}