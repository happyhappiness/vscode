				    "Too many arguments");
				return ARCHIVE_WARN;
			}
			numbers[argc++] = (unsigned long)mtree_atol(&p);
		}
		if (argc < 2) {
			archive_set_error(a, ARCHIVE_ERRNO_FILE_FORMAT,
