int for_each_file_in_obj_subdir(unsigned int subdir_nr,
				struct strbuf *path,
				each_loose_object_fn obj_cb,
				each_loose_cruft_fn cruft_cb,
				each_loose_subdir_fn subdir_cb,
				void *data)
{
	size_t origlen, baselen;
	DIR *dir;
	struct dirent *de;
	int r = 0;

	if (subdir_nr > 0xff)
		BUG("invalid loose object subdirectory: %x", subdir_nr);

	origlen = path->len;
	strbuf_complete(path, '/');
	strbuf_addf(path, "%02x", subdir_nr);
	baselen = path->len;

	dir = opendir(path->buf);
	if (!dir) {
		if (errno != ENOENT)
			r = error_errno("unable to open %s", path->buf);
		strbuf_setlen(path, origlen);
		return r;
	}

	while ((de = readdir(dir))) {
		if (is_dot_or_dotdot(de->d_name))
			continue;

		strbuf_setlen(path, baselen);
		strbuf_addf(path, "/%s", de->d_name);

		if (strlen(de->d_name) == GIT_SHA1_HEXSZ - 2)  {
			char hex[GIT_MAX_HEXSZ+1];
			struct object_id oid;

			xsnprintf(hex, sizeof(hex), "%02x%s",
				  subdir_nr, de->d_name);
			if (!get_oid_hex(hex, &oid)) {
				if (obj_cb) {
					r = obj_cb(&oid, path->buf, data);
					if (r)
						break;
				}
				continue;
			}
		}

		if (cruft_cb) {
			r = cruft_cb(de->d_name, path->buf, data);
			if (r)
				break;
		}
	}
	closedir(dir);

	strbuf_setlen(path, baselen);
	if (!r && subdir_cb)
		r = subdir_cb(subdir_nr, path->buf, data);

	strbuf_setlen(path, origlen);

	return r;
}