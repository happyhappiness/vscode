static struct merge_file_info merge_file_one(struct merge_options *o,
					 const char *path,
					 const unsigned char *o_sha, int o_mode,
					 const unsigned char *a_sha, int a_mode,
					 const unsigned char *b_sha, int b_mode,
					 const char *branch1,
					 const char *branch2)
{
	struct diff_filespec one, a, b;

	one.path = a.path = b.path = (char *)path;
	hashcpy(one.sha1, o_sha);
	one.mode = o_mode;
	hashcpy(a.sha1, a_sha);
	a.mode = a_mode;
	hashcpy(b.sha1, b_sha);
	b.mode = b_mode;
	return merge_file_1(o, &one, &a, &b, branch1, branch2);
}