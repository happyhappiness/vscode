void

squid_getrusage(struct rusage *r)
{

    memset(r, '\0', sizeof(struct rusage));
#if HAVE_GETRUSAGE && defined(RUSAGE_SELF)
#if _SQUID_SOLARIS_
    /* Solaris 2.5 has getrusage() permission bug -- Arjan de Vet */
    enter_suid();
#endif

    getrusage(RUSAGE_SELF, r);
#if _SQUID_SOLARIS_

    leave_suid();
#endif
#endif
}