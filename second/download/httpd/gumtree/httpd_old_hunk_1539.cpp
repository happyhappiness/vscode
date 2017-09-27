
    rv = apr_file_mktemp(&dobj->hfd, dobj->tempfile,
                         APR_CREATE | APR_WRITE | APR_BINARY |
                         APR_BUFFERED | APR_EXCL, r->pool);

    if (rv != APR_SUCCESS) {
        return rv;
    }

    disk_info.format = DISK_FORMAT_VERSION;
    disk_info.date = info->date;
    disk_info.expire = info->expire;
