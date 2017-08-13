		return (ARCHIVE_FATAL);
	}

	v7tar = (struct v7tar *)calloc(1, sizeof(*v7tar));
	if (v7tar == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate v7tar data");
		return (ARCHIVE_FATAL);
	}
	a->format_data = v7tar;
	a->format_name = "tar (non-POSIX)";
	a->format_options = archive_write_v7tar_options;
