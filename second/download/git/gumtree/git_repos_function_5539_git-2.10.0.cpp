static void read_head_pointers(void)
{
	if (read_ref("HEAD", head_sha1))
		die("No HEAD -- no initial commit yet?");
	if (read_ref("MERGE_HEAD", merge_head_sha1)) {
		fprintf(stderr, "Not in the middle of a merge.\n");
		exit(0);
	}
}