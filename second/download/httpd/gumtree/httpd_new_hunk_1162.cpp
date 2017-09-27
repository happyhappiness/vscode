    if (cache->cached
        && ((r->finfo.filetype == APR_REG)
            || ((r->finfo.filetype == APR_DIR)
                && (!r->path_info || !*r->path_info)))
        && (cache->dir_conf_tested == sec_ent)
        && (strcmp(entry_dir, cache->cached) == 0)) {

        int familiar = 0;

        /* Well this looks really familiar!  If our end-result (per_dir_result)
         * didn't change, we have absolutely nothing to do :)
         * Otherwise (as is the case with most dir_merged/file_merged requests)
         * we must merge our dir_conf_merged onto this new r->per_dir_config.
         */
        if (r->per_dir_config == cache->per_dir_result) {
            familiar = 1;
        }

        else if (r->per_dir_config == cache->dir_conf_merged) {
            r->per_dir_config = cache->per_dir_result;
            familiar = 1;
        }
        if (familiar) {
            apr_finfo_t thisinfo;
            int res;
            allow_options_t opts;
            core_dir_config *this_dir;

            this_dir = ap_get_module_config(r->per_dir_config, &core_module);
            opts = this_dir->opts;
            /*
             * If Symlinks are allowed in general we do not need the following
             * check.
             */
            if (!(opts & OPT_SYM_LINKS)) {
                rv = apr_stat(&thisinfo, r->filename,
                              APR_FINFO_MIN | APR_FINFO_NAME | APR_FINFO_LINK,
                              r->pool);
                /*
                 * APR_INCOMPLETE is as fine as result as APR_SUCCESS as we
                 * have added APR_FINFO_NAME to the wanted parameter of
                 * apr_stat above. On Unix platforms this means that apr_stat
                 * is always going to return APR_INCOMPLETE in the case that
                 * the call to the native stat / lstat did not fail.
                 */
                if ((rv != APR_INCOMPLETE) && (rv != APR_SUCCESS)) {
                    /*
                     * This should never happen, because we did a stat on the
                     * same file, resolving a possible symlink several lines
                     * above. Therefore do not make a detailed analysis of rv
                     * in this case for the reason of the failure, just bail out
                     * with a HTTP_FORBIDDEN in case we hit a race condition
                     * here.
                     */
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "access to %s failed; stat of '%s' failed.",
                                  r->uri, r->filename);
                    return r->status = HTTP_FORBIDDEN;
                }
                if (thisinfo.filetype == APR_LNK) {
                    /* Is this a possibly acceptable symlink? */
                    if ((res = resolve_symlink(r->filename, &thisinfo,
                                               opts, r->pool)) != OK) {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                      "Symbolic link not allowed "
                                      "or link target not accessible: %s",
                                      r->filename);
                        return r->status = res;
                    }
                }
            }
            return OK;
        }

        if (cache->walked->nelts) {
            now_merged = ((walk_walked_t*)cache->walked->elts)
                [cache->walked->nelts - 1].merged;
