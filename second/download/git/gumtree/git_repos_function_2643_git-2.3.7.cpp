int create_symref(const char *ref_target, const char *refs_heads_master,
		  const char *logmsg)
{
	const char *lockpath;
	char ref[1000];
	int fd, len, written;
	char *git_HEAD = git_pathdup("%s", ref_target);
	unsigned char old_sha1[20], new_sha1[20];

	if (logmsg && read_ref(ref_target, old_sha1))
		hashclr(old_sha1);

	if (safe_create_leading_directories(git_HEAD) < 0)
		return error("unable to create directory for %s", git_HEAD);

#ifndef NO_SYMLINK_HEAD
	if (prefer_symlink_refs) {
		unlink(git_HEAD);
		if (!symlink(refs_heads_master, git_HEAD))
			goto done;
		fprintf(stderr, "no symlink - falling back to symbolic ref\n");
	}
#endif

	len = snprintf(ref, sizeof(ref), "ref: %s\n", refs_heads_master);
	if (sizeof(ref) <= len) {
		error("refname too long: %s", refs_heads_master);
		goto error_free_return;
	}
	lockpath = mkpath("%s.lock", git_HEAD);
	fd = open(lockpath, O_CREAT | O_EXCL | O_WRONLY, 0666);
	if (fd < 0) {
		error("Unable to open %s for writing", lockpath);
		goto error_free_return;
	}
	written = write_in_full(fd, ref, len);
	if (close(fd) != 0 || written != len) {
		error("Unable to write to %s", lockpath);
		goto error_unlink_return;
	}
	if (rename(lockpath, git_HEAD) < 0) {
		error("Unable to create %s", git_HEAD);
		goto error_unlink_return;
	}
	if (adjust_shared_perm(git_HEAD)) {
		error("Unable to fix permissions on %s", lockpath);
	error_unlink_return:
		unlink_or_warn(lockpath);
	error_free_return:
		free(git_HEAD);
		return -1;
	}

#ifndef NO_SYMLINK_HEAD
	done:
#endif
	if (logmsg && !read_ref(refs_heads_master, new_sha1))
		log_ref_write(ref_target, old_sha1, new_sha1, logmsg);

	free(git_HEAD);
	return 0;
}