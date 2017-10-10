	return (struct commit *) commit;
}

static void fill_blob_sha1(struct commit *commit, struct diff_filespec *spec)
{
	unsigned mode;
	unsigned char sha1[20];

	if (get_tree_entry(commit->object.oid.hash, spec->path,
			   sha1, &mode))
		die("There is no path %s in the commit", spec->path);
	fill_filespec(spec, sha1, 1, mode);

	return;
}

static void fill_line_ends(struct diff_filespec *spec, long *lines,
			   unsigned long **line_ends)
