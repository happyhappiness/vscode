
	fsck_handle_reflog_sha1(refname, osha1);
	fsck_handle_reflog_sha1(refname, nsha1);
	return 0;
}

static int fsck_handle_reflog(const char *logname, const unsigned char *sha1, int flag, void *cb_data)
{
	for_each_reflog_ent(logname, fsck_handle_reflog_ent, (void *)logname);
	return 0;
}

static int fsck_handle_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	struct object *obj;

	obj = parse_object(sha1);
	if (!obj) {
		error("%s: invalid sha1 pointer %s", refname, sha1_to_hex(sha1));
		errors_found |= ERROR_REACHABLE;
		/* We'll continue with the rest despite the error.. */
		return 0;
	}
	if (obj->type != OBJ_COMMIT && is_branch(refname))
		error("%s: not a commit", refname);
