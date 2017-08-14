static int64_t
file_skip_lseek(struct archive *a, void *client_data, int64_t request)
{
	struct read_file_data *mine = (struct read_file_data *)client_data;
#if defined(_WIN32) && !defined(__CYGWIN__)
	/* We use _lseeki64() on Windows. */
	int64_t old_offset, new_offset;
#else
	off_t old_offset, new_offset;
#endif

	/* We use off_t here because lseek() is declared that way. */

	/* TODO: Deal with case where off_t isn't 64 bits.
	 * This shouldn't be a problem on Linux or other POSIX
	 * systems, since the configuration logic for libarchive
	 * tries to obtain a 64-bit off_t.
	 */
	if ((old_offset = lseek(mine->fd, 0, SEEK_CUR)) >= 0 &&
	    (new_offset = lseek(mine->fd, request, SEEK_CUR)) >= 0)
		return (new_offset - old_offset);

	/* If lseek() fails, don't bother trying again. */
	mine->use_lseek = 0;

	/* Let libarchive recover with read+discard */
	if (errno == ESPIPE)
		return (0);

	/* If the input is corrupted or truncated, fail. */
	if (mine->filename_type == FNT_STDIN)
		archive_set_error(a, errno, "Error seeking in stdin");
	else if (mine->filename_type == FNT_MBS)
		archive_set_error(a, errno, "Error seeking in '%s'",
		    mine->filename.m);
	else
		archive_set_error(a, errno, "Error seeking in '%S'",
		    mine->filename.w);
	return (-1);
}