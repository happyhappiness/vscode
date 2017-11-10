static int register_replace_ref(const char *refname,
				const struct object_id *oid,
				int flag, void *cb_data)
{
	/* Get sha1 from refname */
	const char *slash = strrchr(refname, '/');
	const char *hash = slash ? slash + 1 : refname;
	struct replace_object *repl_obj = xmalloc(sizeof(*repl_obj));

	if (strlen(hash) != 40 || get_sha1_hex(hash, repl_obj->original)) {
		free(repl_obj);
		warning("bad replace ref name: %s", refname);
		return 0;
	}

	/* Copy sha1 from the read ref */
	hashcpy(repl_obj->replacement, oid->hash);

	/* Register new object */
	if (register_replace_object(repl_obj, 1))
		die("duplicate replace ref: %s", refname);

	return 0;
}