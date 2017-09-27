ap_log_rerror(APLOG_MARK, APLOG_ERR|APLOG_TOCLIENT, 0, r,
			  "Premature end of script headers: %s", 
                          apr_filename_of_pathname(r->filename));