#endif

#ifdef OS
    printf(" -D OS=\"" OS "\"\n");
#endif

#ifdef HAVE_SHMGET
    printf(" -D HAVE_SHMGET\n");
#endif

#if APR_FILE_BASED_SHM
    printf(" -D APR_FILE_BASED_SHM\n");
