{
		struct archive_string as;
		archive_string_init(&as);
		archive_strcpy(&as, "./");
		archive_strncat(&as, p, len);
		archive_string_empty(&file->parentdir);
		archive_string_concat(&file->parentdir, &as);
		archive_string_free(&as);
		p = file->parentdir.s;
		len = archive_strlen(&file->parentdir);
	}