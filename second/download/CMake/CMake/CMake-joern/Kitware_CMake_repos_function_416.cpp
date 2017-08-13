static int
file_new(struct archive_write *a, struct archive_entry *entry,
    struct file **newfile)
{
	struct _7zip *zip;
	struct file *file;
	const char *u16;
	size_t u16len;
	int ret = ARCHIVE_OK;

	zip = (struct _7zip *)a->format_data;
	*newfile = NULL;

	file = calloc(1, sizeof(*file));
	if (file == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}

	if (0 > archive_entry_pathname_l(entry, &u16, &u16len, zip->sconv)) {
		if (errno == ENOMEM) {
			free(file);
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for UTF-16LE");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "A filename cannot be converted to UTF-16LE;"
		    "You should disable making Joliet extension");
		ret = ARCHIVE_WARN;
	}
	file->utf16name = malloc(u16len + 2);
	if (file->utf16name == NULL) {
		free(file);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for Name");
		return (ARCHIVE_FATAL);
	}
	memcpy(file->utf16name, u16, u16len);
	file->utf16name[u16len+0] = 0;
	file->utf16name[u16len+1] = 0;
	file->name_len = (unsigned)u16len;
	file->mode = archive_entry_mode(entry);
	if (archive_entry_filetype(entry) == AE_IFREG)
		file->size = archive_entry_size(entry);
	else
		archive_entry_set_size(entry, 0);
	if (archive_entry_filetype(entry) == AE_IFDIR)
		file->dir = 1;
	else if (archive_entry_filetype(entry) == AE_IFLNK)
		file->size = strlen(archive_entry_symlink(entry));
	if (archive_entry_mtime_is_set(entry)) {
		file->flg |= MTIME_IS_SET;
		file->times[MTIME].time = archive_entry_mtime(entry);
		file->times[MTIME].time_ns = archive_entry_mtime_nsec(entry);
	}
	if (archive_entry_atime_is_set(entry)) {
		file->flg |= ATIME_IS_SET;
		file->times[ATIME].time = archive_entry_atime(entry);
		file->times[ATIME].time_ns = archive_entry_atime_nsec(entry);
	}
	if (archive_entry_ctime_is_set(entry)) {
		file->flg |= CTIME_IS_SET;
		file->times[CTIME].time = archive_entry_ctime(entry);
		file->times[CTIME].time_ns = archive_entry_ctime_nsec(entry);
	}

	*newfile = file;
	return (ret);
}