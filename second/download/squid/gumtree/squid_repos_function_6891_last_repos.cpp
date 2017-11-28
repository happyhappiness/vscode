void Esi::Clean()
{
    assert(prCustom); // we should be called once, and only after Init()

#if HAVE_LIBEXPAT
    delete prExpat;
    prExpat = NULL;
#endif

#if HAVE_LIBXML2
    delete prLibxml;
    prLibxml = NULL;
#endif

    delete prCustom;
    prCustom = NULL;
}