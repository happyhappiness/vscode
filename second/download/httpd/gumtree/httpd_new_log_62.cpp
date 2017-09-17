ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, NULL,
		   ap_psprintf(p,
			       "pid file %s overwritten -- Unclean shutdown of previous apache run?",
			       fname)
		   );