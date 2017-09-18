    }

    return HTTP_INTERNAL_SERVER_ERROR;        /* If we make it this far,
                                                 we failed. They lose! */

need_2_fields:
    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
		"map file %s, line %d syntax error: requires at "
                "least two fields", r->uri, imap->line_number);
    /* fall through */
menu_bail:
    ap_cfg_closefile(imap);
    if (showmenu) {
