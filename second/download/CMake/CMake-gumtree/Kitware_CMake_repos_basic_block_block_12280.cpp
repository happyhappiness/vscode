{
			if (*p == '\0') {
				archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
				    "Missing number");
				return ARCHIVE_WARN;
			}
			if (argc >= MAX_PACK_ARGS) {
				archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
				    "Too many arguments");
				return ARCHIVE_WARN;
			}
			numbers[argc++] = (unsigned long)mtree_atol(&p);
		}