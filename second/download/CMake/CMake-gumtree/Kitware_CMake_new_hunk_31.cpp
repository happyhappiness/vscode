		if (strcmp(key, "md5") == 0 || strcmp(key, "md5digest") == 0)
			break;
		if (strcmp(key, "mode") == 0) {
			if (val[0] >= '0' && val[0] <= '7') {
				*parsed_kws |= MTREE_HAS_PERM;
				archive_entry_set_perm(entry,
				    (mode_t)mtree_atol(&val, 8));
			} else {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Symbolic or non-octal mode \"%s\" unsupported", val);
				return ARCHIVE_WARN;
			}
			break;
