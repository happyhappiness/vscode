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
