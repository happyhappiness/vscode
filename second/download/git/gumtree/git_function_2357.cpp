static int fsck_cruft(const char *basename, const char *path, void *data)
{
	if (!starts_with(basename, "tmp_obj_"))
		fprintf(stderr, "bad sha1 file: %s\n", path);
	return 0;
}