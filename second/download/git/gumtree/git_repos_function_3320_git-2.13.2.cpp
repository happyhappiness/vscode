int head_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	struct object_id oid;
	int flag;

	if (submodule) {
		if (resolve_gitlink_ref(submodule, "HEAD", oid.hash) == 0)
			return fn("HEAD", &oid, 0, cb_data);

		return 0;
	}

	if (!read_ref_full("HEAD", RESOLVE_REF_READING, oid.hash, &flag))
		return fn("HEAD", &oid, flag, cb_data);

	return 0;
}