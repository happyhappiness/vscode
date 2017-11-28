int
RFCNB_Set_Timeout(int seconds)
{
    /* If we are on a Bezerkeley system, use sigvec, else sigaction */
#if HAVE_SIGACTION
    struct sigaction inact, outact;
#else
    struct sigvec invec, outvec;
#endif

    RFCNB_Timeout = seconds;

    if (RFCNB_Timeout > 0) {	/* Set up handler to ignore but not restart */

#if HAVE_SIGACTION
        inact.sa_handler = (void (*)()) rfcnb_alarm;
        sigemptyset(&inact.sa_mask);
        inact.sa_flags = 0;	/* Don't restart */

        if (sigaction(SIGALRM, &inact, &outact) < 0)
            return (-1);
#else
        invec.sv_handler = (void (*)()) rfcnb_alarm;
        invec.sv_mask = 0;
        invec.sv_flags = SV_INTERRUPT;

        if (sigvec(SIGALRM, &invec, &outvec) < 0)
            return (-1);
#endif

    }
    return (0);

}