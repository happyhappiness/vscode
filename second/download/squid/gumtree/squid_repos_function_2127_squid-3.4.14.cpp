size_t
mem_hdr::writeAvailable(mem_node *aNode, int64_t location, size_t amount, char const *source)
{
    /* if we attempt to overwrite existing data or leave a gap within a node */
    assert (location == aNode->nodeBuffer.offset + (int64_t)aNode->nodeBuffer.length);
    /* And we are not at the end of the node */
    assert (aNode->canAccept (location));

    /* these two can go I think */
    assert (location - aNode->nodeBuffer.offset == (int64_t)aNode->nodeBuffer.length);
    size_t copyLen = min(amount, aNode->space());

    memcpy(aNode->nodeBuffer.data + aNode->nodeBuffer.length, source, copyLen);

    debugs(19, 9, HERE << this << " hi: " << inmem_hi);
    if (inmem_hi <= location)
        inmem_hi = location + copyLen;

    /* Adjust the ptr and len according to what was deposited in the page */
    aNode->nodeBuffer.length += copyLen;

    debugs(19, 9, HERE << this << " hi: " << inmem_hi);
    debugs(19, 9, HERE << this << " hi: " << endOffset());
    return copyLen;
}