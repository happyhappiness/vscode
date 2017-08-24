{
		archive_strncpy(as, header->prefix, sizeof(header->prefix));
		if (as->s[archive_strlen(as) - 1] != '/')
			archive_strappend_char(as, '/');
		archive_strncat(as, header->name, sizeof(header->name));
	}