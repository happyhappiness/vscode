{
		for (i = 0; i < nd + pd; i++)
			archive_strappend_char(&mtree->buf, ' ');
		archive_strcat(&mtree->buf, s);
		s += strlen(s);
	}