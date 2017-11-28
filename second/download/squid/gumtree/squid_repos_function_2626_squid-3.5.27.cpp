int

rusage_maxrss(struct rusage *r)
{
#if _SQUID_SGI_ && _ABIAPI
    return r->ru_pad[0];
#elif _SQUID_SGI_|| _SQUID_OSF_ || _SQUID_AIX_ || defined(BSD4_4)

    return r->ru_maxrss;
#elif defined(HAVE_GETPAGESIZE) && HAVE_GETPAGESIZE != 0

    return (r->ru_maxrss * getpagesize()) >> 10;
#elif defined(PAGESIZE)

    return (r->ru_maxrss * PAGESIZE) >> 10;
#else

    return r->ru_maxrss;
#endif
}