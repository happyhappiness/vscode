				name, typename(type));

	buf = read_sha1_file(sha1, &type, &size);
	if (!buf)
		return error("%s: unable to read file.", name);

	ret = run_gpg_verify(buf, size, flags);

	free(buf);
	return ret;
}

static int git_verify_tag_config(const char *var, const char *value, void *cb)
