{
			if (x == NULL)
				x = r;
			archive_strncat(&mtree->buf, s, x - s);
			archive_strncat(&mtree->buf, " \\\n", 3);
			for (i = 0; i < (INDENTNAMELEN + 1 + pd); i++)
				archive_strappend_char(&mtree->buf, ' ');
			s = r = ++x;
			x = NULL;
		}