void
MemAllocatorProxy::free(void *address)
{
    getAllocator()->free(address);
    /* TODO: check for empty, and if so, if the default type has altered,
     * switch
     */
}