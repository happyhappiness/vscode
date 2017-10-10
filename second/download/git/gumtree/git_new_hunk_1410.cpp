			     one, two, xfrm_msg, must_show_header,
			     o, complete_rewrite);
	else
		fprintf(o->file, "* Unmerged path %s\n", name);
}

static void diff_fill_oid_info(struct diff_filespec *one)
{
	if (DIFF_FILE_VALID(one)) {
		if (!one->oid_valid) {
			struct stat st;
			if (one->is_stdin) {
				oidclr(&one->oid);
