void *
Mem::AllocatorProxy::alloc()
{
    return getAllocator()->alloc();
}