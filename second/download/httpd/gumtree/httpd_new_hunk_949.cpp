
#ifdef NO_LINGCLOSE
    printf(" -D NO_LINGCLOSE\n");
#endif

#if APR_HAVE_IPV6
    printf(" -D APR_HAVE_IPV6 (IPv4-mapped addresses ");
#ifdef AP_ENABLE_V4_MAPPED
    printf("enabled)\n");
#else
    printf("disabled)\n");
#endif
#endif

#if APR_USE_FLOCK_SERIALIZE
    printf(" -D APR_USE_FLOCK_SERIALIZE\n");
#endif

