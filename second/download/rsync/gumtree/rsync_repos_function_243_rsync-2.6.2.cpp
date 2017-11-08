static void delete_one(char *fn, int is_dir)
{
	if (!is_dir) {
		if (robust_unlink(fn) != 0) {
			rprintf(FERROR, "delete_one: unlink %s failed: %s\n",
				full_fname(fn), strerror(errno));
		} else if (verbose) {
			rprintf(FINFO, "deleting %s\n", fn);
		}
	} else {
		if (do_rmdir(fn) != 0) {
			if (errno != ENOTEMPTY && errno != EEXIST) {
				rprintf(FERROR, "delete_one: rmdir %s failed: %s\n",
					full_fname(fn), strerror(errno));
			}
		} else if (verbose) {
			rprintf(FINFO, "deleting directory %s\n", fn);
		}
	}
}