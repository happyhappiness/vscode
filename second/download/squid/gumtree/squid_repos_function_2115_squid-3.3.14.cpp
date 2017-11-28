int
mem_hdr::appendToNode(mem_node *aNode, const char *data, int maxLength)
{
    size_t result = writeAvailable (aNode, aNode->nodeBuffer.offset + aNode->nodeBuffer.length ,maxLength, data);
    return result;
}