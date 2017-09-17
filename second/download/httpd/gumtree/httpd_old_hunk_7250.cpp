		ap_log_error(APLOG_MARK, APLOG_ERR, s,
			     "proxy: error creating cache directory %s",
			     c->filename);
	    *p = '/';
	    ++p;
	}
#if defined(__EMX__) || defined(WIN32)
	/* Under OS/2 use rename. */
	if (rename(c->tempfile, c->filename) == -1)
	    ap_log_error(APLOG_MARK, APLOG_ERR, s,
			 "proxy: error renaming cache file %s to %s",
			 c->tempfile, c->filename);
    }
-- apache_1.3.1/src/modules/proxy/proxy_connect.c	1998-06-08 22:23:50.000000000 +0800
