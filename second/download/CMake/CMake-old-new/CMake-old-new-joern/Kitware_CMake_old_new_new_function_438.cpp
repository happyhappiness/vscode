int
__archive_write_program_write(struct archive_write_filter *f,
    struct archive_write_program_data *data, const void *buff, size_t length)
{
	ssize_t ret;
	const char *buf;

	if (data->child == 0)
		return (ARCHIVE_OK);

	buf = buff;
	while (length > 0) {
		ret = child_write(f, data, buf, length);
		if (ret == -1 || ret == 0) {
			archive_set_error(f->archive, EIO,
			    "Can't write to program: %s", data->program_name);
			return (ARCHIVE_FATAL);
		}
		length -= ret;
		buf += ret;
	}
	return (ARCHIVE_OK);
}