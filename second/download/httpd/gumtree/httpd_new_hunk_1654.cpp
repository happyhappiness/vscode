    ++filp;
    prefix_len = strlen(filp);

    dirp = ap_popendir(neg->pool, neg->dir_name);

    if (dirp == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
                    "cannot read directory for multi: %s", neg->dir_name);
        return HTTP_FORBIDDEN;
    }

    while ((dir_entry = readdir(dirp))) {
        request_rec *sub_req;
