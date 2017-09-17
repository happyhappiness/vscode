    }
    r->allowed |= (1 << M_GET);
    if (r->method_number != M_GET) {
        return DECLINED;
    }
    if (r->finfo.st_mode == 0) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
		    "File does not exist: %s",
                    (r->path_info
                     ? ap_pstrcat(r->pool, r->filename, r->path_info, NULL)
                     : r->filename));
        return HTTP_NOT_FOUND;
    }

    if (!(f = ap_pfopen(r->pool, r->filename, "r"))) {
        ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
                    "file permissions deny server access: %s", r->filename);
        return HTTP_FORBIDDEN;
    }

    if ((*state == xbithack_full)
#if !defined(__EMX__) && !defined(WIN32)
    /*  OS/2 dosen't support Groups. */
        && (r->finfo.st_mode & S_IXGRP)
#endif
        ) {
        ap_update_mtime(r, r->finfo.st_mtime);
        ap_set_last_modified(r);
