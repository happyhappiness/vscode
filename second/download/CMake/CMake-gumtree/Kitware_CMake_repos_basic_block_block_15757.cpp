(format_octal(archive_entry_rdevmajor(entry),
		    h + GNUTAR_rdevmajor_offset,
			GNUTAR_rdevmajor_size)) {
			archive_set_error(&a->archive, ERANGE,
			    "Major device number too large");
			ret = ARCHIVE_FAILED;
		}