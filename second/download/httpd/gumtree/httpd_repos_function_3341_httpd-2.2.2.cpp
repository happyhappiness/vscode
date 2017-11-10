static apr_exit_why_e why_from_exit_code(DWORD exit) {
    /* See WinNT.h STATUS_ACCESS_VIOLATION and family for how
     * this class of failures was determined
     */
    if (((exit & 0xC0000000) == 0xC0000000) 
                    && !(exit & 0x3FFF0000))
        return APR_PROC_SIGNAL;
    else
        return APR_PROC_EXIT;

    /* ### No way to tell if Dr Watson grabbed a core, AFAICT. */
}