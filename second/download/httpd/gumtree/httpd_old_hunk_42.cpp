    else if (strcmp(depth, "1") == 0) {
        return 1;
    }

    /* The caller will return an HTTP_BAD_REQUEST. This will augment the
     * default message that Apache provides. */
    ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                  "An invalid Depth header was specified.");
    return -1;
}

static int dav_get_overwrite(request_rec *r)
{
