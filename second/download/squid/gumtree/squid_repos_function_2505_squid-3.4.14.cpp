void
MemBlob::memAlloc(const size_type minSize)
{
    size_t actualAlloc = minSize;

    Must(!mem);
    mem = static_cast<char*>(memAllocString(actualAlloc, &actualAlloc));
    Must(mem);

    capacity = actualAlloc;
    size = 0;
    debugs(MEMBLOB_DEBUGSECTION, 8,
           id << " memAlloc: requested=" << minSize <<
           ", received=" << capacity);
    ++Stats.live;
    ++Stats.alloc;
    Stats.liveBytes += capacity;
}