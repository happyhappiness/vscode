int64_t
mem_hdr::freeDataUpto(int64_t target_offset)
{
    /* keep the last one to avoid change to other part of code */

    SplayNode<mem_node*> const * theStart = nodes.start();

    while ((theStart = nodes.start())) {
        if (theStart == nodes.finish())
            break;

        if (theStart->data->end() > target_offset )
            break;

        if (!unlink(theStart->data))
            break;
    }

    assert (lowestOffset () <= target_offset);

    return lowestOffset ();
}