{
		archive_string_empty(&mtree->ebuf);
		archive_strncat(&mtree->ebuf, "..\n\n", (mtree->dironly)?3:4);
		mtree_indent(mtree);
	}