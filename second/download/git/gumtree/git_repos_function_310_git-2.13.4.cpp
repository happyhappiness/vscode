static int ce_compare_gitlink(const struct cache_entry *ce)
{
	unsigned char sha1[20];

	/*
	 * We don't actually require that the .git directory
	 * under GITLINK directory be a valid git directory. It
	 * might even be missing (in case nobody populated that
	 * sub-project).
	 *
	 * If so, we consider it always to match.
	 */
	if (resolve_gitlink_ref(ce->name, "HEAD", sha1) < 0)
		return 0;
	return hashcmp(sha1, ce->oid.hash);
}