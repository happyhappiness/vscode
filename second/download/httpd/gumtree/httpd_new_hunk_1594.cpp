                error_fmt = "unable to include \"%s\" in parsed file %s";
            }
#ifndef WIN32
            ap_chdir_file(r->filename);
#endif
            if (error_fmt) {
                ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR,
			    r, error_fmt, tag_val, r->filename);
                ap_rputs(error, r);
            }

	    /* destroy the sub request if it's not a nested include */
            if (rr != NULL
		&& ap_get_module_config(rr->request_config, &includes_module)
