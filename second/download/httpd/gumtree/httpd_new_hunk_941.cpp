	&& (!r->header_only || (d->content_md5 & 1))) {

	/* we need to protect ourselves in case we die while we've got the

 	 * file mmapped */

	mm = mmap(NULL, r->finfo.st_size, PROT_READ, MAP_PRIVATE,

		  fileno(f), 0);

	if (mm == (caddr_t)-1) {

	    ap_log_rerror(APLOG_MARK, APLOG_CRIT, r,

			 "default_handler: mmap failed: %s", r->filename);

	}

    }

    else {

	mm = (caddr_t)-1;

    }

++ apache_1.3.2/src/main/http_log.c	1998-09-22 01:29:45.000000000 +0800

