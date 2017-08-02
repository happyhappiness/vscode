archive_set_error(&a->archive, ERANGE,
		    "Numeric group ID %jd too large",
		    (intmax_t)archive_entry_gid(entry))