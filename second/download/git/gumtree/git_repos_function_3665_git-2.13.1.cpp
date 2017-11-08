static int merge_file_one(struct merge_options *o,
					 const char *path,
					 const struct object_id *o_oid, int o_mode,
					 const struct object_id *a_oid, int a_mode,
					 const struct object_id *b_oid, int b_mode,
					 const char *branch1,
					 const char *branch2,
					 struct merge_file_info *mfi)
{
	struct diff_filespec one, a, b;

	one.path = a.path = b.path = (char *)path;
	oidcpy(&one.oid, o_oid);
	one.mode = o_mode;
	oidcpy(&a.oid, a_oid);
	a.mode = a_mode;
	oidcpy(&b.oid, b_oid);
	b.mode = b_mode;
	return merge_file_1(o, &one, &a, &b, branch1, branch2, mfi);
}