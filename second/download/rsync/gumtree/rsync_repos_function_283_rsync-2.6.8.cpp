mode_t dest_mode(mode_t flist_mode, mode_t cur_mode, int exists)
{
	/* If the file already exists, we'll return the local permissions,
	 * possibly tweaked by the --executability option. */
	if (exists) {
		if (preserve_executability && S_ISREG(flist_mode)) {
			/* If the source file is executable, grant execute
			 * rights to everyone who can read, but ONLY if the
			 * file isn't already executable. */
			if (!(flist_mode & 0111))
				cur_mode &= ~0111;
			else if (!(cur_mode & 0111))
				cur_mode |= (cur_mode & 0444) >> 2;
		}
	} else
		cur_mode = flist_mode & ACCESSPERMS & ~orig_umask;
	if (daemon_chmod_modes && !S_ISLNK(flist_mode))
		cur_mode = tweak_mode(cur_mode, daemon_chmod_modes);
	return (flist_mode & ~CHMOD_BITS) | (cur_mode & CHMOD_BITS);
}