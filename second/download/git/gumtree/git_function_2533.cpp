static int rename_tmp_log(const char *newrefname)
{
	int attempts_remaining = 4;
	struct strbuf path = STRBUF_INIT;
	int ret = -1;

 retry:
	strbuf_reset(&path);
	strbuf_git_path(&path, "logs/%s", newrefname);
	switch (safe_create_leading_directories_const(path.buf)) {
	case SCLD_OK:
		break; /* success */
	case SCLD_VANISHED:
		if (--attempts_remaining > 0)
			goto retry;
		/* fall through */
	default:
		error("unable to create directory for %s", newrefname);
		goto out;
	}

	if (rename(git_path(TMP_RENAMED_LOG), path.buf)) {
		if ((errno==EISDIR || errno==ENOTDIR) && --attempts_remaining > 0) {
			/*
			 * rename(a, b) when b is an existing
			 * directory ought to result in ISDIR, but
			 * Solaris 5.8 gives ENOTDIR.  Sheesh.
			 */
			if (remove_empty_directories(&path)) {
				error("Directory not empty: logs/%s", newrefname);
				goto out;
			}
			goto retry;
		} else if (errno == ENOENT && --attempts_remaining > 0) {
			/*
			 * Maybe another process just deleted one of
			 * the directories in the path to newrefname.
			 * Try again from the beginning.
			 */
			goto retry;
		} else {
			error("unable to move logfile "TMP_RENAMED_LOG" to logs/%s: %s",
				newrefname, strerror(errno));
			goto out;
		}
	}
	ret = 0;
out:
	strbuf_release(&path);
	return ret;
}