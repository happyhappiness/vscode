static void proces_result_codes(RESULTCODES codes, 
                                int *exitcode, 
                                apr_exit_why_e *exitwhy)
{
    int result = 0;
    apr_exit_why_e why = APR_PROC_EXIT;

    switch (codes.codeTerminate) {
    case TC_EXIT:        /* Normal exit */
        why = APR_PROC_EXIT;
        result = codes.codeResult;
        break;

    case TC_HARDERROR:   /* Hard error halt */
        why = APR_PROC_SIGNAL;
        result = SIGSYS;
        break;

    case TC_KILLPROCESS: /* Was killed by a DosKillProcess() */
        why = APR_PROC_SIGNAL;
        result = SIGKILL;
        break;

    case TC_TRAP:        /* TRAP in 16 bit code */
    case TC_EXCEPTION:   /* Threw an exception (32 bit code) */
        why = APR_PROC_SIGNAL;

        switch (codes.codeResult | XCPT_FATAL_EXCEPTION) {
        case XCPT_ACCESS_VIOLATION:
            result = SIGSEGV;
            break;

        case XCPT_ILLEGAL_INSTRUCTION:
            result = SIGILL;
            break;

        case XCPT_FLOAT_DIVIDE_BY_ZERO:
        case XCPT_INTEGER_DIVIDE_BY_ZERO:
            result = SIGFPE;
            break;

        default:
            result = codes.codeResult;
            break;
        }
    }

    if (exitcode) {
        *exitcode = result;
    }

    if (exitwhy) {
        *exitwhy = why;
    }
}