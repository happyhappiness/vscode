(format_number(archive_entry_rdevminor(entry),
		    h + USTAR_rdevminor_offset, USTAR_rdevminor_size,
		    USTAR_rdevminor_max_size, strict)) {
			archive_set_error(&a->archive, ERANGE,
			    "Minor device number too large");
			ret = ARCHIVE_FAILED;
		}