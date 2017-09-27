    apr_file_printf(f, "%%error\n%s\n", error);

    apr_file_close(f);
    return ret;
}

/* Soak up stderr from a script and redirect it to the error log.
 */
static apr_status_t log_script_err(request_rec *r, apr_file_t *script_err)
{
    char argsbuffer[HUGE_STRING_LEN];
    char *newline;
    apr_status_t rv;
