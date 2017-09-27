/*
 * This routine is called when the -t command-line option is supplied.
 * It executes only once, in the startup process, after the check_config
 * phase and just before the process exits.  At this point the module
 * may output any information useful in configuration testing.
 *
 * This is a VOID hook: all defined handlers get called.
 */
static void x_test_config(apr_pool_t *pconf, server_rec *s)
{
    apr_file_t *out = NULL;

    apr_file_open_stderr(&out, pconf);

    apr_file_printf(out, "Example module configuration test routine\n");

    trace_startup(pconf, s, NULL, "x_test_config()");
}

/*
 * This routine is called to perform any module-specific log file
 * openings. It is invoked just before the post_config phase
