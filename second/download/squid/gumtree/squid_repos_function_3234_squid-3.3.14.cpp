int64_t
mem_node::end() const
{
    return nodeBuffer.offset + nodeBuffer.length;
}