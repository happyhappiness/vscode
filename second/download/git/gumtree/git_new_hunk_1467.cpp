	return (struct commit *) commit;
}

static void fill_blob_sha1(struct commit *commit, struct diff_filespec *spec)
{
	unsigned mode;
	struct object_id oid;

	if (get_tree_entry(commit->object.oid.hash, spec->path,
			   oid.hash, &mode))
		die("There is no path %s in the commit", spec->path);
	fill_filespec(spec, &oid, 1, mode);

	return;
}

static void fill_line_ends(struct diff_filespec *spec, long *lines,
			   unsigned long **line_ends)
