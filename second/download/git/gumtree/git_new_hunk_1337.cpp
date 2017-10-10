		prune_tmp_file(path);
	else
		fprintf(stderr, "bad sha1 file: %s\n", path);
	return 0;
}

static int prune_subdir(unsigned int nr, const char *path, void *data)
{
	if (!show_only)
		rmdir(path);
	return 0;
}

