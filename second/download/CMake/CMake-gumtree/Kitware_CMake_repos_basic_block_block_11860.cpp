(archive_strlen(&file->name) == 0)
		archive_strcat(as, ".");
	else
		archive_string_concat(as, &file->name)