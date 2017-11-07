static void get_non_kept_pack_filenames(struct string_list *fname_list)
{
	DIR *dir;
	struct dirent *e;
	char *fname;
	size_t len;

	if (!(dir = opendir(packdir)))
		return;

	while ((e = readdir(dir)) != NULL) {
		if (!ends_with(e->d_name, ".pack"))
			continue;

		len = strlen(e->d_name) - strlen(".pack");
		fname = xmemdupz(e->d_name, len);

		if (!file_exists(mkpath("%s/%s.keep", packdir, fname)))
			string_list_append_nodup(fname_list, fname);
		else
			free(fname);
	}
	closedir(dir);
}