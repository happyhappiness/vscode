	obj->flags = HAS_OBJ;
	return fsck_obj(obj);
}

static int default_refs;

static void fsck_handle_reflog_oid(const char *refname, struct object_id *oid,
	unsigned long timestamp)
{
	struct object *obj;

	if (!is_null_oid(oid)) {
		obj = lookup_object(oid->hash);
		if (obj && (obj->flags & HAS_OBJ)) {
			if (timestamp && name_objects)
				add_decoration(fsck_walk_options.object_names,
					obj,
					xstrfmt("%s@{%ld}", refname, timestamp));
			obj->used = 1;
			mark_object_reachable(obj);
		} else {
			error("%s: invalid reflog entry %s", refname, oid_to_hex(oid));
			errors_found |= ERROR_REACHABLE;
		}
	}
}

static int fsck_handle_reflog_ent(struct object_id *ooid, struct object_id *noid,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	const char *refname = cb_data;

	if (verbose)
		fprintf(stderr, "Checking reflog %s->%s\n",
			oid_to_hex(ooid), oid_to_hex(noid));

	fsck_handle_reflog_oid(refname, ooid, 0);
	fsck_handle_reflog_oid(refname, noid, timestamp);
	return 0;
}

static int fsck_handle_reflog(const char *logname, const struct object_id *oid,
			      int flag, void *cb_data)
{
