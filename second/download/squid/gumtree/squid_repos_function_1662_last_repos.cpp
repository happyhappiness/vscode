void
cbdataRealFree(cbdata *c, const char *file, const int line)
{
#if WITH_VALGRIND
    void *p = c->data;
#else
    void *p = (void *)&c->data;
#endif

    --cbdataCount;
#if USE_CBDATA_DEBUG
    debugs(45, 3, "Freeing " << p << ' ' << file << ':' << line);
    dlinkDelete(&c->link, &cbdataEntries);
#else
    debugs(45, 9, "Freeing " << p);
#endif

#if WITH_VALGRIND
    cbdata_htable.erase(p);
    delete c;
#else
    /* This is ugly. But: operator delete doesn't get
     * the type parameter, so we can't use that
     * to free the memory.
     * So, we free it ourselves.
     * Note that this means a non-placement
     * new would be a seriously bad idea.
     * Lastly, if we where a templated class,
     * we could use the normal delete operator
     * and it would Just Work. RBC 20030902
     */
    c->cbdata::~cbdata();
#endif
}