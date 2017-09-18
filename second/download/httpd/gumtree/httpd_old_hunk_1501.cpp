#ifdef NEED_HASHBANG_EMUL
    printf(" -D NEED_HASHBANG_EMUL\n");
#endif
#ifdef SHARED_CORE
    printf(" -D SHARED_CORE\n");
#endif
}


/* Some init code that's common between win32 and unix... well actually
 * some of it is #ifdef'd but was duplicated before anyhow.  This stuff
 * is still a mess.
