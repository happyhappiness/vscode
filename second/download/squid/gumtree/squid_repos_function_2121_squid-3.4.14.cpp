int64_t
mem_hdr::lowestOffset () const
{
    const SplayNode<mem_node *> *theStart = nodes.start();

    if (theStart)
        return theStart->data->nodeBuffer.offset;

    return 0;
}