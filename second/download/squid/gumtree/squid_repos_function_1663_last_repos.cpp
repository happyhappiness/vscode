void *
cbdataInternalFree(void *p, const char *file, int line)
{
    cbdata *c;
#if WITH_VALGRIND
    c = cbdata_htable.at(p);
#else
    c = (cbdata *) (((char *) p) - cbdata::Offset);
#endif
#if USE_CBDATA_DEBUG
    debugs(45, 3, p << " " << file << ":" << line);
#else
    debugs(45, 9, p);
#endif

    c->check(__LINE__);
    assert(c->valid);
    c->valid = 0;
#if USE_CBDATA_DEBUG

    c->addHistory("Free", file, line);
#endif

    if (c->locks) {
        debugs(45, 9, p << " has " << c->locks << " locks, not freeing");
        return NULL;
    }

    cbdataRealFree(c, file, line);
    return NULL;
}