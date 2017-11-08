int mingw_offset_1st_component(const char *path)
{
	int offset = 0;
	if (has_dos_drive_prefix(path))
		offset = 2;

	/* unc paths */
	else if (is_dir_sep(path[0]) && is_dir_sep(path[1])) {

		/* skip server name */
		char *pos = strpbrk(path + 2, "\\/");
		if (!pos)
			return 0; /* Error: malformed unc path */

		do {
			pos++;
		} while (*pos && !is_dir_sep(*pos));

		offset = pos - path;
	}

	return offset + is_dir_sep(path[offset]);
}