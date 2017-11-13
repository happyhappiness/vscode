static void dump_config_name(const char *fname, apr_pool_t *p)
{
    unsigned i, recursion, line_number;
    void *data;
    apr_file_t *out = NULL;

    apr_file_open_stdout(&out, p);

    /* ap_include_sentinel is defined by the core Include directive; use it to
     * figure out how deep in the stack we are.
     */
    apr_pool_userdata_get(&data, "ap_include_sentinel", p);

    if (data) {
        recursion = *(unsigned *)data;
    } else {
        recursion = 0;
    }

    /* Indent once for each level. */
    for (i = 0; i < (recursion + 1); ++i) {
        apr_file_printf(out, "  ");
    }

    /* ap_include_lineno is similarly defined to tell us where in the last
     * config file we were.
     */
    apr_pool_userdata_get(&data, "ap_include_lineno", p);

    if (data) {
        line_number = *(unsigned *)data;
    } else {
        line_number = 0;
    }

    /* Print the line number and the name of the parsed file. */
    if (line_number > 0) {
        apr_file_printf(out, "(%u)", line_number);
    } else {
        apr_file_printf(out, "(*)");
    }

    apr_file_printf(out, " %s\n", fname);
}