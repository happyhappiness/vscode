{
			archive_set_error(&a->archive, EINVAL,
			    "Can't find long filename for entry");
			archive_entry_copy_pathname(entry, filename);
			/* Parse the time, owner, mode, size fields. */
			ar_parse_common_header(ar, entry, h);
			return (ARCHIVE_WARN);
		}