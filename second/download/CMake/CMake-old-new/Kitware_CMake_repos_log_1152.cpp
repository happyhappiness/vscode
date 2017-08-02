archive_string_sprintf(&shar->work,
			    "mknod %s c %ju %ju\n", shar->quoted_name.s,
			    (uintmax_t)archive_entry_rdevmajor(entry),
			    (uintmax_t)archive_entry_rdevminor(entry))