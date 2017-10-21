	if (verbose >= 5 && !set_path_only)
		rprintf(FINFO, "[%s] change_dir(%s)\n", who_am_i(), curr_dir);

	return 1;
}

/**
 * Return a quoted string with the full pathname of the indicated filename.
 * The string " (in MODNAME)" may also be appended.  The returned pointer
 * remains valid until the next time full_fname() is called.
 **/
char *full_fname(const char *fn)
