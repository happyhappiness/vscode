(fn) {
			fn = 0;
			for (i = 0; i < nd + pd; i++)
				archive_strappend_char(&mtree->buf, ' ');
			archive_strncat(&mtree->buf, s, r - s);
			if (nd + (r -s) > INDENTNAMELEN) {
				archive_strncat(&mtree->buf, " \\\n", 3);
				for (i = 0; i < (INDENTNAMELEN + 1 + pd); i++)
					archive_strappend_char(&mtree->buf, ' ');
			} else {
				for (i = (int)(r -s + nd);
				    i < (INDENTNAMELEN + 1); i++)
					archive_strappend_char(&mtree->buf, ' ');
			}
			s = ++r;
			x = NULL;
			continue;
		}