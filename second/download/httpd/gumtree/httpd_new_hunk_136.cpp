        return DECLINED;
    }

    /* OK, nothing easy.  Trot out the heavy artillery... */

    if (allow_opts & OPT_INDEXES) {
        int errstatus;

        if ((errstatus = ap_discard_request_body(r)) != OK) {
            return errstatus;
        }

        /* KLUDGE --- make the sub_req lookups happen in the right directory.
         * Fixing this in the sub_req_lookup functions themselves is difficult,
         * and would probably break virtual includes...
         */

        if (r->filename[strlen(r->filename) - 1] != '/') {
            r->filename = apr_pstrcat(r->pool, r->filename, "/", NULL);
        }
        return index_directory(r, d);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Directory index forbidden by rule: %s", r->filename);
        return HTTP_FORBIDDEN;
    }
}

static void register_hooks(apr_pool_t *p)
