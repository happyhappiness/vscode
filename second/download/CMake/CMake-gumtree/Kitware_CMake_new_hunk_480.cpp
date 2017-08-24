				    "Missing number");
				return ARCHIVE_WARN;
			}
			numbers[argc++] = (unsigned long)mtree_atol(&p);
			if (argc > MAX_PACK_ARGS) {
				archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
				    "Too many arguments");
