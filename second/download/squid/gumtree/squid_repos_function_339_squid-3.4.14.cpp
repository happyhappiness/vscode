int
check_gss_err(OM_uint32 major_status, OM_uint32 minor_status,
              const char *function, int log, int sout)
{
    if (GSS_ERROR(major_status)) {
        OM_uint32 maj_stat, min_stat;
        OM_uint32 msg_ctx = 0;
        gss_buffer_desc status_string;
        char buf[1024];
        size_t len;

        len = 0;
        msg_ctx = 0;
        do {
            /* convert major status code (GSS-API error) to text */
            maj_stat = gss_display_status(&min_stat, major_status,
                                          GSS_C_GSS_CODE, GSS_C_NULL_OID, &msg_ctx, &status_string);
            if (maj_stat == GSS_S_COMPLETE && status_string.length > 0) {
                if (sizeof(buf) > len + status_string.length + 1) {
                    snprintf(buf + len, (sizeof(buf) - len), "%s", (char *) status_string.value);
                    len += status_string.length;
                }
            } else
                msg_ctx = 0;
            gss_release_buffer(&min_stat, &status_string);
        } while (msg_ctx);
        if (sizeof(buf) > len + 2) {
            snprintf(buf + len, (sizeof(buf) - len), "%s", ". ");
            len += 2;
        }
        msg_ctx = 0;
        do {
            /* convert minor status code (underlying routine error) to text */
            maj_stat = gss_display_status(&min_stat, minor_status,
                                          GSS_C_MECH_CODE, GSS_C_NULL_OID, &msg_ctx, &status_string);
            if (maj_stat == GSS_S_COMPLETE && status_string.length > 0) {
                if (sizeof(buf) > len + status_string.length) {
                    snprintf(buf + len, (sizeof(buf) - len), "%s", (char *) status_string.value);
                    len += status_string.length;
                }
            } else
                msg_ctx = 0;
            gss_release_buffer(&min_stat, &status_string);
        } while (msg_ctx);
        debug((char *) "%s| %s: ERROR: %s failed: %s\n", LogTime(), PROGRAM, function, buf);
        if (sout)
            fprintf(stdout, "BH %s failed: %s\n", function, buf);
        if (log)
            fprintf(stderr, "%s| %s: INFO: User not authenticated\n", LogTime(),
                    PROGRAM);
        return (1);
    }
    return (0);
}