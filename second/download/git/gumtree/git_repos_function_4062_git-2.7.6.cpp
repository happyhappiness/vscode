static int is_eol_crlf(xdfile_t *file, int i)
{
	long size;

	if (i < file->nrec - 1)
		/* All lines before the last *must* end in LF */
		return (size = file->recs[i]->size) > 1 &&
			file->recs[i]->ptr[size - 2] == '\r';
	if (!file->nrec)
		/* Cannot determine eol style from empty file */
		return -1;
	if ((size = file->recs[i]->size) &&
			file->recs[i]->ptr[size - 1] == '\n')
		/* Last line; ends in LF; Is it CR/LF? */
		return size > 1 &&
			file->recs[i]->ptr[size - 2] == '\r';
	if (!i)
		/* The only line has no eol */
		return -1;
	/* Determine eol from second-to-last line */
	return (size = file->recs[i - 1]->size) > 1 &&
		file->recs[i - 1]->ptr[size - 2] == '\r';
}