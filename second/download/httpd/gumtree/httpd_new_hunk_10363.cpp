    }

    return HTTP_INTERNAL_SERVER_ERROR;        /* If we make it this far,
                                                 we failed. They lose! */

need_2_fields:
    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		"map file %s, line %d syntax error: requires at "
                "least two fields", r->uri, imap->line_number);
    /* fall through */
menu_bail:
    ap_cfg_closefile(imap);
    if (showmenu) {
++ apache_1.3.2/src/modules/standard/mod_include.c	1998-09-07 11:42:03.000000000 +0800
