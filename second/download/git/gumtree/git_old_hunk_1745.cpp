		printf("Removing stale temporary file %s\n", fullpath);
	if (!show_only)
		unlink_or_warn(fullpath);
	return 0;
}

static int prune_object(const char *fullpath, const unsigned char *sha1)
{
	struct stat st;
	if (lstat(fullpath, &st))
		return error("Could not stat '%s'", fullpath);
	if (st.st_mtime > expire)
		return 0;
	if (show_only || verbose) {
		enum object_type type = sha1_object_info(sha1, NULL);
		printf("%s %s\n", sha1_to_hex(sha1),
		       (type > 0) ? typename(type) : "unknown");
	}
	if (!show_only)
		unlink_or_warn(fullpath);
	return 0;
}

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

static void prune_object_dir(const char *path)
{
	struct strbuf buf = STRBUF_INIT;
	size_t baselen;
	int i;

	strbuf_addstr(&buf, path);
	strbuf_addch(&buf, '/');
	baselen = buf.len;

	for (i = 0; i < 256; i++) {
		strbuf_addf(&buf, "%02x", i);
		prune_dir(i, &buf);
		strbuf_setlen(&buf, baselen);
	}
}

/*
 * Write errors (particularly out of space) can result in
 * failed temporary packs (and more rarely indexes and other
 * files beginning with "tmp_") accumulating in the object
