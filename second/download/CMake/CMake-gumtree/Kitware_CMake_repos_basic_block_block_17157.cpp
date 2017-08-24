{
	struct shar *shar;
	int ret;

	/*
	 * TODO: Accumulate list of directory names/modes and
	 * fix them all up at end-of-archive.
	 */

	shar = (struct shar *)a->format_data;

	/*
	 * Only write the end-of-archive markers if the archive was
	 * actually started.  This avoids problems if someone sets
	 * shar format, then sets another format (which would invoke
	 * shar_finish to free the format-specific data).
	 */
	if (shar->wrote_header == 0)
		return (ARCHIVE_OK);

	archive_strcat(&shar->work, "exit\n");

	ret = __archive_write_output(a, shar->work.s, shar->work.length);
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	/* Shar output is never padded. */
	archive_write_set_bytes_in_last_block(&a->archive, 1);
	/*
	 * TODO: shar should also suppress padding of
	 * uncompressed data within gzip/bzip2 streams.
	 */

	return (ARCHIVE_OK);
}