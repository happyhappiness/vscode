int offset_1st_component(const char *path)
{
	if (has_dos_drive_prefix(path))
		return 2 + is_dir_sep(path[2]);
	return is_dir_sep(path[0]);
}