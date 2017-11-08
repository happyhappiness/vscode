void putline(apr_file_t *f, const char *l)
{
    apr_status_t rv;
    if (f == NULL)
        return;
    rv = apr_file_puts(l, f);
    if (rv != APR_SUCCESS) {
        apr_file_printf(errfile, "Error writing temp file: %pm", &rv);
        apr_file_close(f);
        exit(ERR_FILEPERM);
    }
}