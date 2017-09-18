r(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR|APLOG_TOCLIENT, 0, r,
			  "%s: %s", malformed, 
                          apr_filename_of_pathname(r->filename));