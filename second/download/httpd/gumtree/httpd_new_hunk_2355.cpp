    ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, r->server,
		MODNAME ": revision_suffix checking %s", r->filename);
#endif /* MIME_MAGIC_DEBUG */

    /* check for recognized revision suffix */
    suffix_pos = strlen(r->filename) - 1;
    if (!ap_isdigit(r->filename[suffix_pos])) {
	return 0;
    }
    while (suffix_pos >= 0 && ap_isdigit(r->filename[suffix_pos]))
	suffix_pos--;
    if (suffix_pos < 0 || r->filename[suffix_pos] != '@') {
	return 0;
    }

    /* perform sub-request for the file name without the suffix */
