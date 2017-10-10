	if (!should_update_submodules())
		return NULL;

	return submodule_from_path(null_sha1, ce->name);
}

static int has_remote(const char *refname, const struct object_id *oid,
		      int flags, void *cb_data)
{
	return 1;
}

