{
	if (!starts_with(basename, "tmp_obj_"))
		fprintf(stderr, "bad sha1 file: %s\n", path);
	return 0;
}

static int fsck_subdir(unsigned int nr, const char *path, void *progress)
{
	display_progress(progress, nr + 1);
	return 0;
}

static void fsck_object_dir(const char *path)
