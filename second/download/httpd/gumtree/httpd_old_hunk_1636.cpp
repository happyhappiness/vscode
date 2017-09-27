    else {
        /* no last slash, buh?! */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "internal error in mod_cern_meta: %s", r->filename);
        /* should really barf, but hey, let's be friends... */
        return DECLINED;
    }

    metafilename = apr_pstrcat(r->pool, scrap_book, "/",
               dconf->metadir ? dconf->metadir : DEFAULT_METADIR,
               "/", real_file,
         dconf->metasuffix ? dconf->metasuffix : DEFAULT_METASUFFIX,
               NULL);
