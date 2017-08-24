{
		struct _7z_header_info header;

		memset(&header, 0, sizeof(header));
		r = slurp_central_directory(a, zip, &header);
		free_Header(&header);
		if (r != ARCHIVE_OK)
			return (r);
		zip->entries_remaining = (size_t)zip->numFiles;
		zip->entry = zip->entries;
	}