int verify_path(const char *path)
{
	char c;

	if (has_dos_drive_prefix(path))
		return 0;

	goto inside;
	for (;;) {
		if (!c)
			return 1;
		if (is_dir_sep(c)) {
inside:
			if (protect_hfs && is_hfs_dotgit(path))
				return 0;
			if (protect_ntfs && is_ntfs_dotgit(path))
				return 0;
			c = *path++;
			if ((c == '.' && !verify_dotfile(path)) ||
			    is_dir_sep(c) || c == '\0')
				return 0;
		}
		c = *path++;
	}
}