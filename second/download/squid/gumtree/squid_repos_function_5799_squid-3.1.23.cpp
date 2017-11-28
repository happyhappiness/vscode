void
MemImplementingAllocator::free(void *obj)
{
    assert(obj != NULL);
    (void) VALGRIND_CHECK_MEM_IS_ADDRESSABLE(obj, obj_size);
    deallocate(obj, MemPools::GetInstance().mem_idle_limit == 0);
    ++free_calls;
}