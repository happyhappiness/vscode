void *
cbdataInternalAlloc(cbdata_type type, const char *file, int line)
{
    cbdata *c;
    void *p;
    assert(type > 0 && type <= cbdata_types);
    /* placement new: the pool alloc gives us cbdata + user type memory space
     * and we init it with cbdata at the start of it
     */
#if WITH_VALGRIND
    c = new cbdata;
    p = cbdata_index[type].pool->alloc();
    c->data = p;
    cbdata_htable.emplace(p,c);
#else
    c = new (cbdata_index[type].pool->alloc()) cbdata;
    p = (void *)&c->data;
#endif

    c->type = type;
    c->valid = 1;
    c->locks = 0;
    c->cookie = (long) c ^ cbdata::Cookie;
    ++cbdataCount;
#if USE_CBDATA_DEBUG

    c->file = file;
    c->line = line;
    c->calls = std::vector<CBDataCall *> ();
    c->addHistory("Alloc", file, line);
    dlinkAdd(c, &c->link, &cbdataEntries);
    debugs(45, 3, "Allocating " << p << " " << file << ":" << line);
#else
    debugs(45, 9, "Allocating " << p);
#endif

    return p;
}