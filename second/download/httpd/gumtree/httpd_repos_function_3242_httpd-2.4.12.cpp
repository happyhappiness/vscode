static void log_data_core(const char *file, int line, int module_index,
                          int level, const server_rec *s,
                          const conn_rec *c, const request_rec *r,
                          const char *label, const void *data, apr_size_t len,
                          unsigned int flags)
{
    unsigned char buf[LOG_BYTES_BUFFER_SIZE];
    apr_size_t off;
    char prefix[20];

    if (!(flags & AP_LOG_DATA_SHOW_OFFSET)) {
        prefix[0] = '\0';
    }

    if (len > 0xffff) { /* bug in caller? */
        len = 0xffff;
    }

    if (label) {
        log_error_va_glue(file, line, module_index, level, APR_SUCCESS, s,
                          c, r, NULL, "%s (%" APR_SIZE_T_FMT " bytes)",
                          label, len);
    }

    off = 0;
    while (off < len) {
        if (flags & AP_LOG_DATA_SHOW_OFFSET) {
            apr_snprintf(prefix, sizeof prefix, "%04x: ", (unsigned int)off);
        }
        fmt_data(buf, data, len, &off);
        log_error_va_glue(file, line, module_index, level, APR_SUCCESS, s,
                          c, r, NULL, "%s%s", prefix, buf);
    }
}