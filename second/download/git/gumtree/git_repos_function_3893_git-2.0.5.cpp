static int prune_dir(int i, struct strbuf *path)
{
	size_t baselen = path->len;
	DIR *dir = opendir(path->buf);
	struct dirent *de;

	if (!dir)
		return 0;

	while ((de = readdir(dir)) != NULL) {
		char name[100];
		unsigned char sha1[20];

		if (is_dot_or_dotdot(de->d_name))
			continue;
		if (strlen(de->d_name) == 38) {
			sprintf(name, "%02x", i);
			memcpy(name+2, de->d_name, 39);
			if (get_sha1_hex(name, sha1) < 0)
				break;

			/*
			 * Do we know about this object?
			 * It must have been reachable
			 */
			if (lookup_object(sha1))
				continue;

			strbuf_addf(path, "/%s", de->d_name);
			prune_object(path->buf, sha1);
			strbuf_setlen(path, baselen);
			continue;
		}
		if (starts_with(de->d_name, "tmp_obj_")) {
			strbuf_addf(path, "/%s", de->d_name);
			prune_tmp_file(path->buf);
			strbuf_setlen(path, baselen);
			continue;
		}
		fprintf(stderr, "bad sha1 file: %s/%s\n", path->buf, de->d_name);
	}
	closedir(dir);
	if (!show_only)
		rmdir(path->buf);
	return 0;
}