archive_set_error(&(a->archive), errno,
			    "Can't read temporary file(%jd)",
			    (intmax_t)rs)