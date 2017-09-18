 * with a .htaccess file which turns FollowSymLinks back on --- and
 * access in such a case must be denied.  So, whatever it is that
 * checks FollowSymLinks needs to know the state of the options as
 * they change, all the way down.
 */

/*
 * We don't want people able to serve up pipes, or unix sockets, or other
 * scary things.  Note that symlink tests are performed later.
 */
static int check_safe_file(request_rec *r)
{

    if (r->finfo.filetype == 0      /* doesn't exist */
        || r->finfo.filetype == APR_DIR
        || r->finfo.filetype == APR_REG
        || r->finfo.filetype == APR_LNK) {
        return OK;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "object is not a file, directory or symlink: %s",
                  r->filename);
    return HTTP_FORBIDDEN;
}

/*
 * resolve_symlink must _always_ be called on an APR_LNK file type!
 * It will resolve the actual target file type, modification date, etc,
 * and provide any processing required for symlink evaluation.
 * Path must already be cleaned, no trailing slash, no multi-slashes,
