void *
memAllocString(size_t net_size, size_t * gross_size)
{
    assert(gross_size);

    auto type = memFindStringSizeType(net_size, true);
    if (type != MEM_NONE) {
        auto &pool = GetStrPool(type);
        *gross_size = pool.objectSize();
        assert(*gross_size >= net_size);
        ++StrCountMeter;
        StrVolumeMeter += *gross_size;
        return pool.alloc();
    }

    *gross_size = net_size;
    ++StrCountMeter;
    StrVolumeMeter += *gross_size;
    return xcalloc(1, net_size);
}