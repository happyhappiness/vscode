
	ret = create_symref_locked(lock, refname, target, logmsg);
	unlock_ref(lock);
	return ret;
}

int reflog_exists(const char *refname)
{
	struct stat st;

	return !lstat(git_path("logs/%s", refname), &st) &&
		S_ISREG(st.st_mode);
