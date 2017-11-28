size_t
mem_node::space() const
{
    return SM_PAGE_SIZE - nodeBuffer.length;
}