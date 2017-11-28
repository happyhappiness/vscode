void *
LeakFinder::free(void *p, const char *file, int line)
{
    assert(p);
    LeakFinderPtr *c = (LeakFinderPtr *) hash_lookup(table, p);
    assert(c);
    hash_remove_link(table, c);
    count--;
    delete c;
    dump();
    return p;
}