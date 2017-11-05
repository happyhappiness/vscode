static void prune_dir(int i, DIR *dir, struct strbuf *pathname, int opts)
{
	struct dirent *de;
	char hex[40];
	int top_len = pathname->len;

	sprintf(hex, "%02x", i);
	while ((de = readdir(dir)) != NULL) {
		unsigned char sha1[20];
		if (strlen(de->d_name) != 38)
			continue;
		memcpy(hex + 2, de->d_name, 38);
		if (get_sha1_hex(hex, sha1))
			continue;
		if (!has_sha1_pack(sha1))
			continue;

		strbuf_add(pathname, de->d_name, 38);
		if (opts & PRUNE_PACKED_DRY_RUN)
			printf("rm -f %s\n", pathname->buf);
		else
			unlink_or_warn(pathname->buf);
		display_progress(progress, i + 1);
		strbuf_setlen(pathname, top_len);
	}
}