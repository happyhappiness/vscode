struct ref_lock *lock_ref_sha1(const char *refname, const unsigned char *old_sha1)
{
	char refpath[PATH_MAX];
	if (check_refname_format(refname, 0))
		return NULL;
	strcpy(refpath, mkpath("refs/%s", refname));
	return lock_ref_sha1_basic(refpath, old_sha1, 0, NULL);
}