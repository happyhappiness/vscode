/*
 * You *could* change the following if you wanted to see the calling
 * sequence reported in the server's error_log, but beware - almost all of
 * these co-routines are called for every single request, and the impact
 * on the size (and readability) of the error_log is considerable.
 */
#ifndef EXAMPLE_LOG_EACH
#define EXAMPLE_LOG_EACH 0
#endif

#if EXAMPLE_LOG_EACH
static void example_log_each(apr_pool_t *p, server_rec *s, const char *note)
{
    if (s != NULL) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "mod_example: %s", note);
    } else {
        apr_file_t *out = NULL;
        apr_file_open_stderr(&out, p);
        apr_file_printf(out, "mod_example traced in non-loggable "
                        "context: %s\n", note);
    }
}
#endif

/*
 * This utility routine traces the hooks called when the server starts up.
 * It leaves a trace in a global variable, so it should not be called from
 * a hook handler that runs in a multi-threaded situation.
 */

static void trace_startup(apr_pool_t *p, server_rec *s, x_cfg *mconfig,
                          const char *note)
{
    const char *sofar;
    char *where, *addon;

#if EXAMPLE_LOG_EACH
    example_log_each(p, s, note);
#endif

    /*
     * If we weren't passed a configuration record, we can't figure out to
     * what location this call applies.  This only happens for co-routines
