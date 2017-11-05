static int split_mail_stgit_series(struct am_state *state, const char **paths,
					int keep_cr)
{
	const char *series_dir;
	char *series_dir_buf;
	FILE *fp;
	struct argv_array patches = ARGV_ARRAY_INIT;
	struct strbuf sb = STRBUF_INIT;
	int ret;

	if (!paths[0] || paths[1])
		return error(_("Only one StGIT patch series can be applied at once"));

	series_dir_buf = xstrdup(*paths);
	series_dir = dirname(series_dir_buf);

	fp = fopen(*paths, "r");
	if (!fp)
		return error(_("could not open '%s' for reading: %s"), *paths,
				strerror(errno));

	while (!strbuf_getline_lf(&sb, fp)) {
		if (*sb.buf == '#')
			continue; /* skip comment lines */

		argv_array_push(&patches, mkpath("%s/%s", series_dir, sb.buf));
	}

	fclose(fp);
	strbuf_release(&sb);
	free(series_dir_buf);

	ret = split_mail_conv(stgit_patch_to_mail, state, patches.argv, keep_cr);

	argv_array_clear(&patches);
	return ret;
}