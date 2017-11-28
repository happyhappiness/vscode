int
mem_hdr::NodeCompare(mem_node * const &left, mem_node * const &right)
{
    // possibly Range can help us at some point.

    if (left->dataRange().intersection(right->dataRange()).size() > 0)
        return 0;

    return *left < *right ? -1 : 1;
}