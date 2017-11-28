void *
MemAllocatorProxy::alloc()
{
    return getAllocator()->alloc();
}