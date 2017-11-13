static char *get_symlink(const struct object_id *oid, const char *path)
{
	char *data;
	if (is_null_oid(oid)) {
		/* The symlink is unknown to Git so read from the filesystem */
		struct strbuf link = STRBUF_INIT;
		if (has_symlinks) {
			if (strbuf_readlink(&link, path, strlen(path)))
				die(_("could not read symlink %s"), path);
		} else if (strbuf_read_file(&link, path, 128))
			die(_("could not read symlink file %s"), path);

		data = strbuf_detach(&link, NULL);
	} else {
		enum object_type type;
		unsigned long size;
		data = read_sha1_file(oid->hash, &type, &size);
		if (!data)
			die(_("could not read object %s for symlink %s"),
				oid_to_hex(oid), path);
	}

	return data;
}