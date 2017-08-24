{
#ifdef EAI_NONAME
    /* rfc3493 conformant */
    error = EAI_NONAME;
#else
    /* rfc3493 obsoleted */
    error = EAI_NODATA;
#endif
#ifdef USE_WINSOCK
    SET_SOCKERRNO(error);
#endif
  }