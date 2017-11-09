static void diff_fill_oid_info(struct diff_filespec *one)
{
	if (DIFF_FILE_VALID(one)) {
		if (!one->oid_valid) {
			struct stat st;
			if (one->is_stdin) {
				oidclr(&one->oid);
				return;
			}
			if (lstat(one->path, &st) < 0)
				die_errno("stat '%s'", one->path);
			if (index_path(one->oid.hash, one->path, &st, 0))
				die("cannot hash %s", one->path);
		}
	}
	else
		oidclr(&one->oid);
}