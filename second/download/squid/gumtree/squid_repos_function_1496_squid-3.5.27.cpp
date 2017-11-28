void *
LeakFinder::touch(void *p, const char *file, int line)
{
    assert(p);
    LeakFinderPtr *c = (LeakFinderPtr *) hash_lookup(table, p);
    assert(c);
    c->file = file;
    c->line = line;
    c->when = squid_curtime;
    return p;
}