archive_read_open_filename(struct archive *a, const char *filename,
    size_t block_size)
{
	const char *filenames[2] = { filename, NULL };
	return archive_read_open_filenames(a, filenames, block_size);
}

int
archive_read_open_filenames(struct archive *a, const char **filenames,
    size_t block_size)
{
	struct read_file_data *mine;
	const char *filename = NULL;
	if (filenames)
		filename = *(filenames++);

	archive_clear_error(a);
	do
	{
		if (filename == NULL)
			filename = "";
		mine = (struct read_file_data *)calloc(1,
			sizeof(*mine) + strlen(filename));
		if (mine == NULL)
			goto no_memory;
		strcpy(mine->filename.m, filename);
		mine->block_size = block_size;
		mine->fd = -1;
		mine->buffer = NULL;
		mine->st_mode = mine->use_lseek = 0;
		if (filename == NULL || filename[0] == '\0') {
			mine->filename_type = FNT_STDIN;
		} else
			mine->filename_type = FNT_MBS;
		if (archive_read_append_callback_data(a, mine) != (ARCHIVE_OK))
			return (ARCHIVE_FATAL);
		if (filenames == NULL)
			break;
		filename = *(filenames++);
	} while (filename != NULL && filename[0] != '\0');
	archive_read_set_open_callback(a, file_open);
	archive_read_set_read_callback(a, file_read);
	archive_read_set_skip_callback(a, file_skip);
	archive_read_set_close_callback(a, file_close);
	archive_read_set_switch_callback(a, file_switch);
	archive_read_set_seek_callback(a, file_seek);

	return (archive_read_open1(a));
no_memory:
	archive_set_error(a, ENOMEM, "No memory");
	return (ARCHIVE_FATAL);
}

int
archive_read_open_filename_w(struct archive *a, const wchar_t *wfilename,
    size_t block_size)
{
	struct read_file_data *mine = (struct read_file_data *)calloc(1,
		sizeof(*mine) + wcslen(wfilename) * sizeof(wchar_t));
	if (!mine)
	{
		archive_set_error(a, ENOMEM, "No memory");
		return (ARCHIVE_FATAL);
	}
	mine->fd = -1;
	mine->block_size = block_size;

	if (wfilename == NULL || wfilename[0] == L'\0') {
		mine->filename_type = FNT_STDIN;
	} else {
#if defined(_WIN32) && !defined(__CYGWIN__)
		mine->filename_type = FNT_WCS;
		wcscpy(mine->filename.w, wfilename);
#else
		/*
		 * POSIX system does not support a wchar_t interface for
		 * open() system call, so we have to translate a whcar_t
		 * filename to multi-byte one and use it.
		 */
		struct archive_string fn;

		archive_string_init(&fn);
		if (archive_string_append_from_wcs(&fn, wfilename,
		    wcslen(wfilename)) != 0) {
			if (errno == ENOMEM)
				archive_set_error(a, errno,
				    "Can't allocate memory");
			else
				archive_set_error(a, EINVAL,
				    "Failed to convert a wide-character"
				    " filename to a multi-byte filename");
			archive_string_free(&fn);
			free(mine);
			return (ARCHIVE_FATAL);
		}
		mine->filename_type = FNT_MBS;
		strcpy(mine->filename.m, fn.s);
		archive_string_free(&fn);
#endif
	}
	if (archive_read_append_callback_data(a, mine) != (ARCHIVE_OK))
		return (ARCHIVE_FATAL);
	archive_read_set_open_callback(a, file_open);
	archive_read_set_read_callback(a, file_read);
	archive_read_set_skip_callback(a, file_skip);
	archive_read_set_close_callback(a, file_close);
	archive_read_set_switch_callback(a, file_switch);
	archive_read_set_seek_callback(a, file_seek);

	return (archive_read_open1(a));
}

static int
file_open(struct archive *a, void *client_data)
{
	struct stat st;
	struct read_file_data *mine = (struct read_file_data *)client_data;
	void *buffer;
	const char *filename = NULL;
	const wchar_t *wfilename = NULL;
