int
Fs::Ufs::UFSSwapDir::mapBitAllocate()
{
    int fn;
    fn = map->allocate(suggest);
    map->setBit(fn);
    suggest = fn + 1;
    return fn;
}