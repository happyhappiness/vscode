void
memDataInit(mem_type type, const char *name, size_t size, int, bool doZero)
{
    assert(name && size);

    if (GetPool(type) != NULL)
        return;

    GetPool(type) = memPoolCreate(name, size);
    GetPool(type)->zeroBlocks(doZero);
}