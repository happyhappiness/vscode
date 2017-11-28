int64_t
mem_hdr::endOffset () const
{
    int64_t result = 0;
    const SplayNode<mem_node *> *theEnd = nodes.finish();

    if (theEnd)
        result = theEnd->data->dataRange().end;

    assert (result == inmem_hi);

    return result;
}