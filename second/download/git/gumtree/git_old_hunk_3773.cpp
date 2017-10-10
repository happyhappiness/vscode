		}
	}

	/* Make sure leading directories are created */
	status = safe_create_leading_directories_const(path);
	if (status) {
		if (status == SCLD_EXISTS) {
			/* something else exists */
			error(msg, path, _(": perhaps a D/F conflict?"));
			return -1;
		}
		die(msg, path, "");
	}

	/*
	 * Do not unlink a file in the work tree if we are not
	 * tracking it.
	 */
	if (would_lose_untracked(path))
		return error(_("refusing to lose untracked file at '%s'"),
			     path);

	/* Successful unlink is good.. */
	if (!unlink(path))
		return 0;
	/* .. and so is no existing file */
	if (errno == ENOENT)
		return 0;
	/* .. but not some other error (who really cares what?) */
	return error(msg, path, _(": perhaps a D/F conflict?"));
}

static void update_file_flags(struct merge_options *o,
			      const unsigned char *sha,
			      unsigned mode,
			      const char *path,
			      int update_cache,
			      int update_wd)
{
	if (o->call_depth)
		update_wd = 0;

	if (update_wd) {
		enum object_type type;
		void *buf;
