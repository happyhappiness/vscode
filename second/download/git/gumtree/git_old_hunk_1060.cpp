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

static int files_verify_refname_available(struct ref_store *ref_store,
					  const char *newname,
					  const struct string_list *extras,
					  const struct string_list *skip,
					  struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, 1, "verify_refname_available");
	struct ref_dir *packed_refs = get_packed_refs(refs);
	struct ref_dir *loose_refs = get_loose_refs(refs);

	if (verify_refname_available_dir(newname, extras, skip,
					 packed_refs, err) ||
	    verify_refname_available_dir(newname, extras, skip,
					 loose_refs, err))
		return -1;

	return 0;
}

static int write_ref_to_lockfile(struct ref_lock *lock,
				 const unsigned char *sha1, struct strbuf *err);
static int commit_ref_update(struct files_ref_store *refs,
			     struct ref_lock *lock,
