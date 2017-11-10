static int for_each_file_in_obj_subdir(int subdir_nr,
				       struct strbuf *path,
				       each_loose_object_fn obj_cb,
				       each_loose_cruft_fn cruft_cb,
				       each_loose_subdir_fn subdir_cb,
				       void *data)
{
	size_t baselen = path->len;
	DIR *dir = opendir(path->buf);
	struct dirent *de;
	int r = 0;

	if (!dir) {
		if (errno == ENOENT)
			return 0;
		return error("unable to open %s: %s", path->buf, strerror(errno));
	}

	while ((de = readdir(dir))) {
		if (is_dot_or_dotdot(de->d_name))
			continue;

		strbuf_setlen(path, baselen);
		strbuf_addf(path, "/%s", de->d_name);

		if (strlen(de->d_name) == 38)  {
			char hex[41];
			unsigned char sha1[20];

			snprintf(hex, sizeof(hex), "%02x%s",
				 subdir_nr, de->d_name);
			if (!get_sha1_hex(hex, sha1)) {
				if (obj_cb) {
					r = obj_cb(sha1, path->buf, data);
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

	return r;
}