size_t
mem_node::StoreMemSize()
{
    return InUseCount() * SM_PAGE_SIZE;
}