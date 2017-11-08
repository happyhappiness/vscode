static int dir_fixups(request_rec *r)
{
    if (r->finfo.filetype == APR_DIR) {
        /* serve up a directory */
        return fixup_dir(r);
    }
    else if ((r->finfo.filetype == APR_NOFILE) && (r->handler == NULL)) {
        /* No handler and nothing in the filesystem - use fallback */
        return fixup_dflt(r);
    }
    return DECLINED;
}