static int git_config_from_blob_ref(config_fn_t fn,
				    const char *name,
				    void *data)
{
	unsigned char sha1[20];

	if (get_sha1(name, sha1) < 0)
		return error("unable to resolve config blob '%s'", name);
	return git_config_from_blob_sha1(fn, name, sha1, data);
}