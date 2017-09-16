	real_file = last_slash;

	real_file++;

	*last_slash = '\0';

    }

    else {

	/* no last slash, buh?! */

	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,

		    "internal error in mod_cern_meta: %s", r->filename);

	/* should really barf, but hey, let's be friends... */

	return DECLINED;

    };



    metafilename = ap_pstrcat(r->pool, "/", scrap_book, "/",

