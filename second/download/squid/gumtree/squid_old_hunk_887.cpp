    else
        fprintf(debug_log, "FATAL: Received signal %d...dying.\n", sig);

#if PRINT_STACK_TRACE
#if _SQUID_HPUX_
    {
        extern void U_STACK_TRACE(void);	/* link with -lcl */
        fflush(debug_log);
        dup2(fileno(debug_log), 2);
        U_STACK_TRACE();
    }

#endif /* _SQUID_HPUX_ */
#if _SQUID_SOLARIS_ && HAVE_LIBOPCOM_STACK
    {				/* get ftp://opcom.sun.ca/pub/tars/opcom_stack.tar.gz and */
        extern void opcom_stack_trace(void);	/* link with -lopcom_stack */
        fflush(debug_log);
        dup2(fileno(debug_log), fileno(stdout));
        opcom_stack_trace();
        fflush(stdout);
    }
