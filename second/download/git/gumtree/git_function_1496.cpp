static void count_objects(DIR *d, char *path, int len, int verbose,
			  unsigned long *loose,
			  off_t *loose_size,
			  unsigned long *packed_loose)
{
	struct dirent *ent;
	while ((ent = readdir(d)) != NULL) {
		char hex[41];
		unsigned char sha1[20];
		const char *cp;
		int bad = 0;

		if (is_dot_or_dotdot(ent->d_name))
			continue;
		for (cp = ent->d_name; *cp; cp++) {
			int ch = *cp;
			if (('0' <= ch && ch <= '9') ||
			    ('a' <= ch && ch <= 'f'))
				continue;
			bad = 1;
			break;
		}
		if (cp - ent->d_name != 38)
			bad = 1;
		else {
			struct stat st;
			memcpy(path + len + 3, ent->d_name, 38);
			path[len + 2] = '/';
			path[len + 41] = 0;
			if (lstat(path, &st) || !S_ISREG(st.st_mode))
				bad = 1;
			else
				(*loose_size) += xsize_t(on_disk_bytes(st));
		}
		if (bad) {
			if (verbose) {
				struct strbuf sb = STRBUF_INIT;
				strbuf_addf(&sb, "%.*s/%s",
					    len + 2, path, ent->d_name);
				report_garbage("garbage found", sb.buf);
				strbuf_release(&sb);
			}
			continue;
		}
		(*loose)++;
		if (!verbose)
			continue;
		memcpy(hex, path+len, 2);
		memcpy(hex+2, ent->d_name, 38);
		hex[40] = 0;
		if (get_sha1_hex(hex, sha1))
			die("internal error");
		if (has_sha1_pack(sha1))
			(*packed_loose)++;
	}
}