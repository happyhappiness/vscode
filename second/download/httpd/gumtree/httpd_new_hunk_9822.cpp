        qsort((void *) candidates->elts, candidates->nelts,
              sizeof(misspelled_file), sort_by_quality);

        /*
         * Conditions for immediate redirection: 
         *     a) the first candidate was not found by stripping the suffix 
         * AND b) there exists only one candidate OR the best match is not
	 *        ambiguous
         * then return a redirection right away.
         */
        if (variant[0].quality != SP_VERYDIFFERENT
	    && (candidates->nelts == 1
		|| variant[0].quality != variant[1].quality)) {

            nuri = ap_pstrcat(r->pool, url, variant[0].name, r->path_info,
			      r->parsed_uri.query ? "?" : "",
			      r->parsed_uri.query ? r->parsed_uri.query : "",
			      NULL);

            ap_table_setn(r->headers_out, "Location",
			  ap_construct_url(r->pool, nuri, r));

            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_INFO, r,
			 ref ? "Fixed spelling: %s to %s from %s"
			     : "Fixed spelling: %s to %s",
			 r->uri, nuri, ref);

            return HTTP_MOVED_PERMANENTLY;
        }
        /*
         * Otherwise, a "[300] Multiple Choices" list with the variants is
         * returned.
