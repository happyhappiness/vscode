bool
mem_hdr::unlink(mem_node *aNode)
{
    if (aNode->write_pending) {
        debugs(0, DBG_CRITICAL, "cannot unlink mem_node " << aNode << " while write_pending");
        return false;
    }

    nodes.remove (aNode, NodeCompare);
    delete aNode;
    return true;
}