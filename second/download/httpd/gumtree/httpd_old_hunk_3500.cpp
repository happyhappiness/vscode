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
