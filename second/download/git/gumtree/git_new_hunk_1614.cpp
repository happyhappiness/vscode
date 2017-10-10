	struct object *obj;
	obj = parse_object_buffer(oid, type, size, buffer, eaten);
	if (!obj) {
		errors_found |= ERROR_OBJECT;
		return error("%s: object corrupt or missing", oid_to_hex(oid));
	}
	obj->flags &= ~(REACHABLE | SEEN);
	obj->flags |= HAS_OBJ;
	return fsck_obj(obj);
}

static int default_refs;

static void fsck_handle_reflog_oid(const char *refname, struct object_id *oid,
