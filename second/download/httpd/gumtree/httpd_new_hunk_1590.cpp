#endif

#ifdef OS
    ap_rputs(" -D OS=\"" OS "\"\n", r);
#endif

#ifdef HAVE_SHMGET
    ap_rputs(" -D HAVE_SHMGET\n", r);
#endif

#if APR_FILE_BASED_SHM
    ap_rputs(" -D APR_FILE_BASED_SHM\n", r);
