static int robust_move(char *src, char *dst)
{
	int keep_trying = 4;
	int keep_path_extfs = 0;
	int failed;

	while (keep_trying) {
		if (keep_path_extfs) {
			failed = copy_file(src, dst, 0755);
			if (!failed) {
				do_unlink(src);
			}
		} else {
			failed = robust_rename (src, dst);
		}

		if (failed) {
			if (verbose > 2)
				rprintf (FERROR, "robust_move failed: %s(%d)\n",
					strerror (errno), errno);
			switch (errno) {
				/* external filesystem */
				case EXDEV:
					keep_path_extfs = 1;
					keep_trying--;
					break;
				/* no directory to write to */
				case ENOENT:
					make_dir (dst, 0755);
					keep_trying--;
					break;
				default:
					keep_trying = 0;
			} /* switch */
		} else
			keep_trying = 0;
	} /* while */
	return (!failed);
}