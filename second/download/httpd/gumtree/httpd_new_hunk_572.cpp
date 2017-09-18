        || r->finfo.filetype == APR_DIR
        || r->finfo.filetype == APR_REG
        || r->finfo.filetype == APR_LNK) {
        return OK;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "object is not a file, directory or symlink: %s",
                  r->filename);
    return HTTP_FORBIDDEN;
}

/*
