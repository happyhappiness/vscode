static int
write_dot_dot_entry(struct archive_write *a, struct mtree_entry *n)
{
	struct mtree_writer *mtree = a->format_data;
	int ret;

	if (n->parentdir.s) {
		if (mtree->indent) {
			int i, pd = mtree->depth * 4;
			for (i = 0; i < pd; i++)
				archive_strappend_char(&mtree->buf, ' ');
		}
		archive_string_sprintf(&mtree->buf, "# %s/%s\n",
			n->parentdir.s, n->basename.s);
	}

	if (mtree->indent) {
		archive_string_empty(&mtree->ebuf);
		archive_strncat(&mtree->ebuf, "..\n\n", (mtree->dironly)?3:4);
		mtree_indent(mtree);
	} else
		archive_strncat(&mtree->buf, "..\n\n", (mtree->dironly)?3:4);

	if (mtree->buf.length > 32768) {
		ret = __archive_write_output(
			a, mtree->buf.s, mtree->buf.length);
		archive_string_empty(&mtree->buf);
	} else
		ret = ARCHIVE_OK;
	return (ret);
}