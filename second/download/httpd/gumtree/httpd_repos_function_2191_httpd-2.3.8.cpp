static void trace_nocontext(apr_pool_t *p, const char *file, int line, 
                            const char *note)
{
    /* 
     * Since we have no request or connection to trace, or any idea
     * from where this routine was called, there's really not much we
     * can do.  If we are not logging everything by way of the
     * EXAMPLE_LOG_EACH constant, do nothing in this routine.
     */

#ifdef EXAMPLE_LOG_EACH
    ap_log_perror(file, line, APLOG_MODULE_INDEX, APLOG_NOTICE, 0, p, "%s", note);
#endif
}