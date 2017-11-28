heap_key
heap_gen_key(heap * hp, heap_t dat)
{
    return hp->gen_key(dat, hp->age);
}