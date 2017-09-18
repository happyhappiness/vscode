	r->content_encoding = tmp;
    }

    /* detect memory allocation or other errors */
    if (!r->content_type ||
	(state == rsl_encoding && !r->content_encoding)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      MODNAME ": unexpected state %d; could be caused by bad "
                      "data in magic file",
                      state);
	return HTTP_INTERNAL_SERVER_ERROR;
    }

