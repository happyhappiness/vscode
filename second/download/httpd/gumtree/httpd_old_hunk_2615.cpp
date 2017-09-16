	if (r->filename[strlen(r->filename) - 1] != '/') {

	    r->filename = ap_pstrcat(r->pool, r->filename, "/", NULL);

	}

	return index_directory(r, d);

    }

    else {

	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

		     "Directory index forbidden by rule: %s", r->filename);

	return HTTP_FORBIDDEN;

    }

}





-- apache_1.3.1/src/modules/standard/mod_cern_meta.c	1998-07-09 01:47:14.000000000 +0800

