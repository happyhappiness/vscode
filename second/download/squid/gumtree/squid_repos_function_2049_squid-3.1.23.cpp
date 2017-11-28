size_t
mem_hdr::copyAvailable(mem_node *aNode, int64_t location, size_t amount, char *target) const
{
    if (aNode->nodeBuffer.offset > location)
        return 0;

    assert (aNode->nodeBuffer.offset <= location);

    assert (aNode->end() > location);

    size_t copyOffset = location - aNode->nodeBuffer.offset;

    size_t copyLen = min(amount, aNode->nodeBuffer.length - copyOffset);

    xmemcpy(target, aNode->nodeBuffer.data + copyOffset, copyLen);

    return copyLen;
}