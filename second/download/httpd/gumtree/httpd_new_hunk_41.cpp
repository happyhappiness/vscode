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

