static void x_test_config(apr_pool_t *pconf, server_rec *s)
{
    apr_file_t *out = NULL;

    apr_file_open_stderr(&out, pconf);

    apr_file_printf(out, "Example module configuration test routine\n");

    trace_startup(pconf, s, NULL, "x_test_config()");
}