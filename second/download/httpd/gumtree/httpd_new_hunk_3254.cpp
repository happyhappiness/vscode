    if ((pc->req_override & (OR_OPTIONS | OR_FILEINFO | OR_INDEXES))
        || ((pc->req_override & RSRC_CONF)
        && ((pc->req_override & (ACCESS_CONF | OR_AUTHCFG | OR_LIMIT))))) {
        printf("anywhere");
    }
    else if (pc->req_override & RSRC_CONF) {
        printf("only outside <Directory>, <Files>, <Location>, or <If>");
    }
    else {
        printf("only inside <Directory>, <Files>, <Location>, or <If>");
    }

    /* Warn if the directive is allowed inside <Directory> or .htaccess
     * but module doesn't support per-dir configuration
     */
    if ((pc->req_override & (OR_ALL | ACCESS_CONF)) && !pm->create_dir_config)
