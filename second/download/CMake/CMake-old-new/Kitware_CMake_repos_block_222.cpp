{
		if (mtree->indent) {
			int i, pd = mtree->depth * 4;
			for (i = 0; i < pd; i++)
				archive_strappend_char(&mtree->buf, ' ');
		}
		archive_string_sprintf(&mtree->buf, "# %s/%s\n",
			n->parentdir.s, n->basename.s);
	}