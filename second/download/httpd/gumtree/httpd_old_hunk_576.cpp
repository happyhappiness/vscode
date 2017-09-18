 x    * APR_DIR test.  But if you accessed /symlink/index.html, for example,
 x    * you would *not* get the 403.
 x
 x   if (r->finfo.filetype != APR_DIR
 x       && (res = resolve_symlink(r->filename, r->info, ap_allow_options(r),
 x                                 r->pool))) {
 x       ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
 x                     "Symbolic link not allowed: %s", r->filename);
 x       return res;
 x   }
 */

    /* Save future sub-requestors much angst in processing
