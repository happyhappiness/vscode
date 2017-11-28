void
mem_hdr::makeAppendSpace()
{
    if (!nodes.size()) {
        appendNode (new mem_node (0));
        return;
    }

    if (!nodes.finish()->data->space())
        appendNode (new mem_node (endOffset()));

    assert (nodes.finish()->data->space());
}