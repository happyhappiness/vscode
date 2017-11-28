int64_t
mem_node::start() const
{
    assert (nodeBuffer.offset >= 0);
    return nodeBuffer.offset;
}