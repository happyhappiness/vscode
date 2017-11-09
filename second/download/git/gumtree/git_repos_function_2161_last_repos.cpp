int mkdir_in_gitdir(const char *path)
{
	if (mkdir(path, 0777)) {
		int saved_errno = errno;
		struct stat st;
		struct strbuf sb = STRBUF_INIT;

		if (errno != EEXIST)
			return -1;
		/*
		 * Are we looking at a path in a symlinked worktree
		 * whose original repository does not yet have it?
		 * e.g. .git/rr-cache pointing at its original
		 * repository in which the user hasn't performed any
		 * conflict resolution yet?
		 */
		if (lstat(path, &st) || !S_ISLNK(st.st_mode) ||
		    strbuf_readlink(&sb, path, st.st_size) ||
		    !is_absolute_path(sb.buf) ||
		    mkdir(sb.buf, 0777)) {
			strbuf_release(&sb);
			errno = saved_errno;
			return -1;
		}
		strbuf_release(&sb);
	}
	return adjust_shared_perm(path);
}