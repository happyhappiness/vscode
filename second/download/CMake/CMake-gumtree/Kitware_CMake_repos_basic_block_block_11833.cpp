{
		iso9660->re_files.first = file->re_next;
		if (iso9660->re_files.first == NULL)
			iso9660->re_files.last =
			    &(iso9660->re_files.first);
	}