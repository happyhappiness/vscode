static int git_config_from_blob_sha1(config_fn_t fn,
				     const char *name,
				     const unsigned char *sha1,
				     void *data)
{
	enum object_type type;
	char *buf;
	unsigned long size;
	int ret;

	buf = read_sha1_file(sha1, &type, &size);
	if (!buf)
		return error("unable to load config blob object '%s'", name);
	if (type != OBJ_BLOB) {
		free(buf);
		return error("reference '%s' does not point to a blob", name);
	}

	ret = git_config_from_mem(fn, "blob", name, buf, size, data);
	free(buf);

	return ret;
}