	obj->flags = HAS_OBJ;
	return fsck_obj(obj);
}

static int default_refs;

static void fsck_handle_reflog_sha1(const char *refname, unsigned char *sha1,
	unsigned long timestamp)
{
	struct object *obj;

	if (!is_null_sha1(sha1)) {
		obj = lookup_object(sha1);
		if (obj && (obj->flags & HAS_OBJ)) {
			if (timestamp && name_objects)
				add_decoration(fsck_walk_options.object_names,
					obj,
					xstrfmt("%s@{%ld}", refname, timestamp));
			obj->used = 1;
			mark_object_reachable(obj);
		} else {
			error("%s: invalid reflog entry %s", refname, sha1_to_hex(sha1));
			errors_found |= ERROR_REACHABLE;
		}
	}
}

static int fsck_handle_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	const char *refname = cb_data;

	if (verbose)
		fprintf(stderr, "Checking reflog %s->%s\n",
			sha1_to_hex(osha1), sha1_to_hex(nsha1));

	fsck_handle_reflog_sha1(refname, osha1, 0);
	fsck_handle_reflog_sha1(refname, nsha1, timestamp);
	return 0;
}

static int fsck_handle_reflog(const char *logname, const struct object_id *oid,
			      int flag, void *cb_data)
{
