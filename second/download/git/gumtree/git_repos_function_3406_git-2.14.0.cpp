int should_autocreate_reflog(const char *refname)
{
	switch (log_all_ref_updates) {
	case LOG_REFS_ALWAYS:
		return 1;
	case LOG_REFS_NORMAL:
		return starts_with(refname, "refs/heads/") ||
			starts_with(refname, "refs/remotes/") ||
			starts_with(refname, "refs/notes/") ||
			!strcmp(refname, "HEAD");
	default:
		return 0;
	}
}