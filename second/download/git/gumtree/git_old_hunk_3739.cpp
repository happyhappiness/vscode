			size, options);

	return report(options, obj, FSCK_MSG_UNKNOWN_TYPE, "unknown type '%d' (internal fsck error)",
			  obj->type);
}

int fsck_error_function(struct object *obj, int msg_type, const char *message)
{
	if (msg_type == FSCK_WARN) {
		warning("object %s: %s", oid_to_hex(&obj->oid), message);
		return 0;
	}
	error("object %s: %s", oid_to_hex(&obj->oid), message);
	return 1;
}
