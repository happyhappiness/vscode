int
RFCNB_Set_Timeout(int seconds)
{
    /* If we are on a Bezerkeley system, use sigvec, else sigaction */

#if ORIGINAL_SAMBA_CODE
#ifndef SA_RESTART
    struct sigvec invec, outvec;
#else
    struct sigaction inact, outact;
#endif

    RFCNB_Timeout = seconds;

    if (RFCNB_Timeout > 0) {    /* Set up handler to ignore but not restart */

#ifndef SA_RESTART
        invec.sv_handler = (void (*)()) rfcnb_alarm;
        invec.sv_mask = 0;
        invec.sv_flags = SV_INTERRUPT;

        if (sigvec(SIGALRM, &invec, &outvec) < 0)
            return (-1);
#else /* !SA_RESTART */
        inact.sa_handler = (void (*)()) rfcnb_alarm;
#ifdef Solaris
        /* Solaris seems to have an array of vectors ... */
        inact.sa_mask.__sigbits[0] = 0;
        inact.sa_mask.__sigbits[1] = 0;
        inact.sa_mask.__sigbits[2] = 0;
        inact.sa_mask.__sigbits[3] = 0;
#else /* !Solaris */
        inact.sa_mask = (sigset_t) 0;
#endif /* Solaris */
        inact.sa_flags = 0;     /* Don't restart */

        if (sigaction(SIGALRM, &inact, &outact) < 0)
            return (-1);

#endif /* !SA_RESTART */

    }
#else /* !ORIGINAL_SAMBA_CODE ADAPTED SQUID CODE */
#if HAVE_SIGACTION
    struct sigaction inact, outact;
#else
    struct sigvec invec, outvec;
#endif

    RFCNB_Timeout = seconds;

    if (RFCNB_Timeout > 0) {    /* Set up handler to ignore but not restart */

#if HAVE_SIGACTION
        inact.sa_handler = (void (*)()) rfcnb_alarm;
        sigemptyset(&inact.sa_mask);
        inact.sa_flags = 0;     /* Don't restart */

        if (sigaction(SIGALRM, &inact, &outact) < 0)
            return (-1);
#else /* !HAVE_SIGACTION */
        invec.sv_handler = (void (*)()) rfcnb_alarm;
        invec.sv_mask = 0;
        invec.sv_flags = SV_INTERRUPT;

        if (sigvec(SIGALRM, &invec, &outvec) < 0)
            return (-1);
#endif /* !HAVE_SIGACTION */
    }
#endif /* !ORIGINAL_SAMBA_CODE ADAPTED SQUID CODE */
    return (0);
}