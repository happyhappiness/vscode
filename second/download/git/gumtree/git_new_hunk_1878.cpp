			return -1;
		}
	}
	return 0;
}

static int rename_ref_available(const char *oldname, const char *newname)
{
	struct string_list skip = STRING_LIST_INIT_NODUP;
	int ret;

	string_list_insert(&skip, oldname);
	ret = is_refname_available(newname, &skip, get_packed_refs(&ref_cache))
	    && is_refname_available(newname, &skip, get_loose_refs(&ref_cache));
	string_list_clear(&skip, 0);
	return ret;
}

static int write_ref_sha1(struct ref_lock *lock, const unsigned char *sha1,
			  const char *logmsg);

int rename_ref(const char *oldrefname, const char *newrefname, const char *logmsg)
{
	unsigned char sha1[20], orig_sha1[20];
	int flag = 0, logmoved = 0;
	struct ref_lock *lock;
	struct stat loginfo;
	int log = !lstat(git_path("logs/%s", oldrefname), &loginfo);
	const char *symref = NULL;

	if (log && S_ISLNK(loginfo.st_mode))
		return error("reflog for %s is a symlink", oldrefname);

	symref = resolve_ref_unsafe(oldrefname, RESOLVE_REF_READING,
				    orig_sha1, &flag);
	if (flag & REF_ISSYMREF)
		return error("refname %s is a symbolic ref, renaming it is not supported",
			oldrefname);
	if (!symref)
		return error("refname %s not found", oldrefname);

	if (!rename_ref_available(oldrefname, newrefname))
		return 1;

	if (log && rename(git_path("logs/%s", oldrefname), git_path(TMP_RENAMED_LOG)))
		return error("unable to move logfile logs/%s to "TMP_RENAMED_LOG": %s",
			oldrefname, strerror(errno));

	if (delete_ref(oldrefname, orig_sha1, REF_NODEREF)) {
		error("unable to delete old %s", oldrefname);
		goto rollback;
	}

	if (!read_ref_full(newrefname, RESOLVE_REF_READING, sha1, NULL) &&
	    delete_ref(newrefname, sha1, REF_NODEREF)) {
		if (errno==EISDIR) {
			if (remove_empty_directories(git_path("%s", newrefname))) {
				error("Directory not empty: %s", newrefname);
				goto rollback;
			}
