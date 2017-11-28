char *
mem_hdr::NodeGet(mem_node * aNode)
{
    assert(!aNode->write_pending);
    aNode->write_pending = true;
    return aNode->data;
}