int

rusage_maxrss(struct rusage *r)
{
#if defined(_SQUID_SGI_) && _ABIAPI
    return r->ru_pad[0];
#elif defined(_SQUID_SGI_)

    return r->ru_maxrss;
#elif defined(_SQUID_OSF_)

    return r->ru_maxrss;
#elif defined(_SQUID_AIX_)

    return r->ru_maxrss;
#elif defined(BSD4_4)

    return r->ru_maxrss;
#elif defined(HAVE_GETPAGESIZE) && HAVE_GETPAGESIZE != 0

    return (r->ru_maxrss * getpagesize()) >> 10;
#elif defined(PAGESIZE)

    return (r->ru_maxrss * PAGESIZE) >> 10;
#else

    return r->ru_maxrss;
#endif
}