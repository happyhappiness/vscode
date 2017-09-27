    /* If there isn't an extension then give it an empty string */
    if (!ext) {
        ext = "";
    }

    /* eliminate the '.' if there is one */
    if (*ext == '.') {
        ++ext;
    }

    /* check if we have a registered command for the extension*/
    new_cmd = apr_table_get(d->file_type_handlers, ext);
    e_info->detached = 1;
    if (new_cmd == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02135)
