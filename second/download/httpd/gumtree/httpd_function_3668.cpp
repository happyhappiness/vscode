apr_status_t ajp_msg_log(request_rec *r, ajp_msg_t *msg, char *err)
{
    int level;
    apr_size_t count;
    char *buf, *next;
    apr_status_t rc = APR_SUCCESS;

    if (APLOGrtrace7(r)) {
        level = APLOG_TRACE7;
        count = 1024;
        if (APLOGrtrace8(r)) {
            level = APLOG_TRACE8;
            count = AJP_MAX_BUFFER_SZ;
        }
        rc = ajp_msg_dump(r->pool, msg, err, count, &buf);
        if (rc == APR_SUCCESS) {
            while ((next = ap_strchr(buf, '\n'))) {
                *next = '\0';
                ap_log_rerror(APLOG_MARK, level, 0, r, "%s", buf);
                buf = next + 1;
            }
            ap_log_rerror(APLOG_MARK, level, 0, r, "%s", buf);
        }
    }
    return rc;
}