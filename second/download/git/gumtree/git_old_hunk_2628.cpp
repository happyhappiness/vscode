		if (res)
			return 1;
	}
	return 0;
}

int delete_ref(const char *refname, const unsigned char *sha1, unsigned int flags)
{
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_delete(transaction, refname,
				   (sha1 && !is_null_sha1(sha1)) ? sha1 : NULL,
				   flags, NULL, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		error("%s", err.buf);
		ref_transaction_free(transaction);
		strbuf_release(&err);
		return 1;
	}
	ref_transaction_free(transaction);
	strbuf_release(&err);
	return 0;
}

/*
 * People using contrib's git-new-workdir have .git/logs/refs ->
 * /some/other/path/.git/logs/refs, and that may live on another device.
 *
 * IOW, to avoid cross device rename errors, the temporary renamed log must
 * live into logs/refs.
 */
#define TMP_RENAMED_LOG  "logs/refs/.tmp-renamed-log"

static int rename_tmp_log(const char *newrefname)
{
	int attempts_remaining = 4;

 retry:
	switch (safe_create_leading_directories_const(git_path("logs/%s", newrefname))) {
	case SCLD_OK:
		break; /* success */
	case SCLD_VANISHED:
		if (--attempts_remaining > 0)
			goto retry;
		/* fall through */
	default:
		error("unable to create directory for %s", newrefname);
		return -1;
	}

	if (rename(git_path(TMP_RENAMED_LOG), git_path("logs/%s", newrefname))) {
		if ((errno==EISDIR || errno==ENOTDIR) && --attempts_remaining > 0) {
			/*
			 * rename(a, b) when b is an existing
			 * directory ought to result in ISDIR, but
			 * Solaris 5.8 gives ENOTDIR.  Sheesh.
			 */
			if (remove_empty_directories(git_path("logs/%s", newrefname))) {
				error("Directory not empty: logs/%s", newrefname);
				return -1;
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
			return -1;
		}
	}
	return 0;
}

static int rename_ref_available(const char *oldname, const char *newname)
{
	struct string_list skip = STRING_LIST_INIT_NODUP;
	struct strbuf err = STRBUF_INIT;
