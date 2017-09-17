     * you access /symlink (or /symlink/) you would get a 403 without this
     * S_ISDIR test.  But if you accessed /symlink/index.html, for example,
     * you would *not* get the 403.
     */
    if (!S_ISDIR(r->finfo.st_mode)
        && (res = check_symlinks(r->filename, ap_allow_options(r)))) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "Symbolic link not allowed: %s", r->filename);
        return res;
    }
    return OK;                  /* Can only "fail" if access denied by the
                                 * symlink goop. */
}
