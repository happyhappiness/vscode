size_t MemAllocator::RoundedSize(size_t s)
{
    return ((s + sizeof(void*) - 1) / sizeof(void*)) * sizeof(void*);
}