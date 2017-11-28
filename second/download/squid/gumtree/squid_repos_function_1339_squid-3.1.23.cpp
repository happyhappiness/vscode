void *

LeakFinder::add
(void *p, const char *file, int line)
{
    assert(hash_lookup(table, p) == NULL);
    LeakFinderPtr *c = new LeakFinderPtr(p, file, line);
    hash_join(table, c);
    count++;
    return p;
}