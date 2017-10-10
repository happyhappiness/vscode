
static void fill_blob_sha1(struct commit *commit, struct diff_filespec *spec)
{
	unsigned mode;
	unsigned char sha1[20];

	if (get_tree_entry(commit->object.sha1, spec->path,
			   sha1, &mode))
		die("There is no path %s in the commit", spec->path);
	fill_filespec(spec, sha1, 1, mode);

	return;
}
