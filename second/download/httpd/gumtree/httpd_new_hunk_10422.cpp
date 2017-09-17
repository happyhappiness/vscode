{
    int suffix_pos, result;
    char *sub_filename;
    request_rec *sub;

#if MIME_MAGIC_DEBUG
    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r,
		MODNAME ": revision_suffix checking %s", r->filename);
#endif /* MIME_MAGIC_DEBUG */

    /* check for recognized revision suffix */
    suffix_pos = strlen(r->filename) - 1;
    if (!ap_isdigit(r->filename[suffix_pos])) {
