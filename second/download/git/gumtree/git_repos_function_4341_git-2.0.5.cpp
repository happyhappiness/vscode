static void fsck_dir(int i, char *path)
{
	DIR *dir = opendir(path);
	struct dirent *de;
	char name[100];

	if (!dir)
		return;

	if (verbose)
		fprintf(stderr, "Checking directory %s\n", path);

	sprintf(name, "%02x", i);
	while ((de = readdir(dir)) != NULL) {
		unsigned char sha1[20];

		if (is_dot_or_dotdot(de->d_name))
			continue;
		if (is_loose_object_file(de, name, sha1)) {
			add_sha1_list(sha1, DIRENT_SORT_HINT(de));
			continue;
		}
		if (starts_with(de->d_name, "tmp_obj_"))
			continue;
		fprintf(stderr, "bad sha1 file: %s/%s\n", path, de->d_name);
	}
	closedir(dir);
}