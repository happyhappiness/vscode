void fmt_output_subject(struct strbuf *filename,
			const char *subject,
			struct rev_info *info)
{
	const char *suffix = info->patch_suffix;
	int nr = info->nr;
	int start_len = filename->len;
	int max_len = start_len + FORMAT_PATCH_NAME_MAX - (strlen(suffix) + 1);

	if (0 < info->reroll_count)
		strbuf_addf(filename, "v%d-", info->reroll_count);
	strbuf_addf(filename, "%04d-%s", nr, subject);

	if (max_len < filename->len)
		strbuf_setlen(filename, max_len);
	strbuf_addstr(filename, suffix);
}