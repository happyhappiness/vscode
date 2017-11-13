static void dav_log_err(request_rec *r, dav_error *err, int level)
{
    dav_error *errscan;

    /* Log the errors */
    /* ### should have a directive to log the first or all */
    for (errscan = err; errscan != NULL; errscan = errscan->prev) {
        if (errscan->desc == NULL)
            continue;

        if (errscan->save_errno != 0) {
            errno = errscan->save_errno;
            ap_log_rerror(APLOG_MARK, level, errno, r, "%s  [%d, #%d]",
                          errscan->desc, errscan->status, errscan->error_id);
        }
        else {
            ap_log_rerror(APLOG_MARK, level, 0, r,
                          "%s  [%d, #%d]",
                          errscan->desc, errscan->status, errscan->error_id);
        }
    }
}