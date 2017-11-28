size_t
Ipc::Mem::PageLimit()
{
    size_t limit = 0;
    for (int i = 0; i < PageId::maxPurpose; ++i)
        limit += PageLimit(i);
    return limit;
}