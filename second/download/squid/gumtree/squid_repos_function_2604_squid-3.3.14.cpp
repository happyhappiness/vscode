int

rusage_pagefaults(struct rusage *r)
{
#if _SQUID_SGI_ && _ABIAPI
    return r->ru_pad[5];
#else

    return r->ru_majflt;
#endif
}