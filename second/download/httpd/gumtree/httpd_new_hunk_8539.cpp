	if (r->filename[strlen(r->filename) - 1] != '/') {
	    r->filename = ap_pstrcat(r->pool, r->filename, "/", NULL);
	}
	return index_directory(r, d);
    }
    else {
	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
		     "Directory index forbidden by rule: %s", r->filename);
	return HTTP_FORBIDDEN;
    }
}


++ apache_1.3.2/src/modules/standard/mod_cern_meta.c	1998-08-14 10:49:56.000000000 +0800
