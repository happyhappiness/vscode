ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_DEBUG, 0, s,
		MODNAME ": apprentice read %d lines, %d rules, %d errors",
		lineno, rule, errs);