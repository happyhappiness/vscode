static int interpret_target(struct walker *walker, char *target, unsigned char *sha1)
{
	if (!get_sha1_hex(target, sha1))
		return 0;
	if (!check_refname_format(target, 0)) {
		struct ref *ref = alloc_ref(target);
		if (!walker->fetch_ref(walker, ref)) {
			hashcpy(sha1, ref->old_oid.hash);
			free(ref);
			return 0;
		}
		free(ref);
	}
	return -1;
}