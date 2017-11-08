static const char *lock_repo_for_gc(int force, pid_t* ret_pid)
{
	static struct lock_file lock;
	char my_host[128];
	struct strbuf sb = STRBUF_INIT;
	struct stat st;
	uintmax_t pid;
	FILE *fp;
	int fd;

	if (pidfile)
		/* already locked */
		return NULL;

	if (gethostname(my_host, sizeof(my_host)))
		strcpy(my_host, "unknown");

	fd = hold_lock_file_for_update(&lock, git_path("gc.pid"),
				       LOCK_DIE_ON_ERROR);
	if (!force) {
		static char locking_host[128];
		int should_exit;
		fp = fopen(git_path("gc.pid"), "r");
		memset(locking_host, 0, sizeof(locking_host));
		should_exit =
			fp != NULL &&
			!fstat(fileno(fp), &st) &&
			/*
			 * 12 hour limit is very generous as gc should
			 * never take that long. On the other hand we
			 * don't really need a strict limit here,
			 * running gc --auto one day late is not a big
			 * problem. --force can be used in manual gc
			 * after the user verifies that no gc is
			 * running.
			 */
			time(NULL) - st.st_mtime <= 12 * 3600 &&
			fscanf(fp, "%"PRIuMAX" %127c", &pid, locking_host) == 2 &&
			/* be gentle to concurrent "gc" on remote hosts */
			(strcmp(locking_host, my_host) || !kill(pid, 0) || errno == EPERM);
		if (fp != NULL)
			fclose(fp);
		if (should_exit) {
			if (fd >= 0)
				rollback_lock_file(&lock);
			*ret_pid = pid;
			return locking_host;
		}
	}

	strbuf_addf(&sb, "%"PRIuMAX" %s",
		    (uintmax_t) getpid(), my_host);
	write_in_full(fd, sb.buf, sb.len);
	strbuf_release(&sb);
	commit_lock_file(&lock);

	pidfile = git_pathdup("gc.pid");
	sigchain_push_common(remove_pidfile_on_signal);
	atexit(remove_pidfile);

	return NULL;
}