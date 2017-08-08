archive_set_error(&a->archive, ERANGE,
		    "Numeric user ID %jd too large",
		    (intmax_t)archive_entry_uid(entry));