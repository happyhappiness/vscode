static int builtin_diff_blobs(struct rev_info *revs,
			      int argc, const char **argv,
			      struct blobinfo *blob)
{
	unsigned mode = canon_mode(S_IFREG | 0644);

	if (argc > 1)
		usage(builtin_diff_usage);

	if (blob[0].mode == S_IFINVALID)
		blob[0].mode = mode;

	if (blob[1].mode == S_IFINVALID)
		blob[1].mode = mode;

	stuff_change(&revs->diffopt,
		     blob[0].mode, blob[1].mode,
		     blob[0].sha1, blob[1].sha1,
		     1, 1,
		     blob[0].name, blob[1].name);
	diffcore_std(&revs->diffopt);
	diff_flush(&revs->diffopt);
	return 0;
}