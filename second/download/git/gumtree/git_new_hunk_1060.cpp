 * People using contrib's git-new-workdir have .git/logs/refs ->
 * /some/other/path/.git/logs/refs, and that may live on another device.
 *
 * IOW, to avoid cross device rename errors, the temporary renamed log must
 * live into logs/refs.
 */
#define TMP_RENAMED_LOG  "refs/.tmp-renamed-log"

struct rename_cb {
	const char *tmp_renamed_log;
	int true_errno;
};

static int rename_tmp_log_callback(const char *path, void *cb_data)
{
	struct rename_cb *cb = cb_data;

	if (rename(cb->tmp_renamed_log, path)) {
		/*
		 * rename(a, b) when b is an existing directory ought
		 * to result in ISDIR, but Solaris 5.8 gives ENOTDIR.
		 * Sheesh. Record the true errno for error reporting,
		 * but report EISDIR to raceproof_create_file() so
		 * that it knows to retry.
		 */
		cb->true_errno = errno;
		if (errno == ENOTDIR)
			errno = EISDIR;
		return -1;
	} else {
		return 0;
	}
}

static int rename_tmp_log(struct files_ref_store *refs, const char *newrefname)
{
	struct strbuf path = STRBUF_INIT;
	struct strbuf tmp = STRBUF_INIT;
	struct rename_cb cb;
	int ret;

	files_reflog_path(refs, &path, newrefname);
	files_reflog_path(refs, &tmp, TMP_RENAMED_LOG);
	cb.tmp_renamed_log = tmp.buf;
	ret = raceproof_create_file(path.buf, rename_tmp_log_callback, &cb);
	if (ret) {
		if (errno == EISDIR)
			error("directory not empty: %s", path.buf);
		else
			error("unable to move logfile %s to %s: %s",
			      tmp.buf, path.buf,
			      strerror(cb.true_errno));
	}

	strbuf_release(&path);
	strbuf_release(&tmp);
	return ret;
}

static int write_ref_to_lockfile(struct ref_lock *lock,
				 const unsigned char *sha1, struct strbuf *err);
static int commit_ref_update(struct files_ref_store *refs,
			     struct ref_lock *lock,
