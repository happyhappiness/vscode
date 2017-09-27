        if ((r->finfo.filetype == APR_DIR) && r->path_info && *r->path_info)
        {
            if ((rv = apr_filepath_merge(&r->path_info, r->filename,
                                         r->path_info,
                                         APR_FILEPATH_NOTABOVEROOT, r->pool))
                != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00033)
                              "dir_walk error, path_info %s is not relative "
                              "to the filename path %s for uri %s",
                              r->path_info, r->filename, r->uri);
                return HTTP_INTERNAL_SERVER_ERROR;
            }

