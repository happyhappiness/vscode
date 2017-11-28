int
UFSSwapDir::mapBitAllocate()
{
    int fn;
    fn = file_map_allocate(map, suggest);
    file_map_bit_set(map, fn);
    suggest = fn + 1;
    return fn;
}