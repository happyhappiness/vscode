static void fsck_handle_reflog_sha1(const char *refname, unsigned char *sha1)
{
	struct object *obj;

	if (!is_null_sha1(sha1)) {
		obj = lookup_object(sha1);
		if (obj) {
			obj->used = 1;
			mark_object_reachable(obj);
		} else {
			error("%s: invalid reflog entry %s", refname, sha1_to_hex(sha1));
			errors_found |= ERROR_REACHABLE;
		}
	}
}