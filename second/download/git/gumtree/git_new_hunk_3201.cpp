	if (size >= 1 && buf[size-1] == '\032')
		stats->nonprintable--;
}

/*
 * The same heuristics as diff.c::mmfile_is_binary()
 * We treat files with bare CR as binary
 */
static int convert_is_binary(unsigned long size, const struct text_stat *stats)
{
	if (stats->lonecr)
		return 1;
	if (stats->nul)
		return 1;
	if ((stats->printable >> 7) < stats->nonprintable)
		return 1;
	return 0;
}

static unsigned int gather_convert_stats(const char *data, unsigned long size)
{
	struct text_stat stats;
	int ret = 0;
	if (!data || !size)
		return 0;
	gather_stats(data, size, &stats);
	if (convert_is_binary(size, &stats))
		ret |= CONVERT_STAT_BITS_BIN;
	if (stats.crlf)
		ret |= CONVERT_STAT_BITS_TXT_CRLF;
	if (stats.lonelf)
		ret |=  CONVERT_STAT_BITS_TXT_LF;

	return ret;
}

static const char *gather_convert_stats_ascii(const char *data, unsigned long size)
{
	unsigned int convert_stats = gather_convert_stats(data, size);

	if (convert_stats & CONVERT_STAT_BITS_BIN)
		return "-text";
	switch (convert_stats) {
	case CONVERT_STAT_BITS_TXT_LF:
		return "lf";
	case CONVERT_STAT_BITS_TXT_CRLF:
		return "crlf";
	case CONVERT_STAT_BITS_TXT_LF | CONVERT_STAT_BITS_TXT_CRLF:
		return "mixed";
	default:
		return "none";
	}
}

const char *get_cached_convert_stats_ascii(const char *path)
{
	const char *ret;
	unsigned long sz;
	void *data = read_blob_data_from_cache(path, &sz);
	ret = gather_convert_stats_ascii(data, sz);
	free(data);
	return ret;
}

const char *get_wt_convert_stats_ascii(const char *path)
{
	const char *ret = "";
	struct strbuf sb = STRBUF_INIT;
	if (strbuf_read_file(&sb, path, 0) >= 0)
		ret = gather_convert_stats_ascii(sb.buf, sb.len);
	strbuf_release(&sb);
	return ret;
}

static int text_eol_is_crlf(void)
{
	if (auto_crlf == AUTO_CRLF_TRUE)
		return 1;
	else if (auto_crlf == AUTO_CRLF_INPUT)
		return 0;
	if (core_eol == EOL_CRLF)
		return 1;
	if (core_eol == EOL_UNSET && EOL_NATIVE == EOL_CRLF)
		return 1;
	return 0;
}

static enum eol output_eol(enum crlf_action crlf_action)
{
	switch (crlf_action) {
	case CRLF_BINARY:
		return EOL_UNSET;
	case CRLF_TEXT_CRLF:
		return EOL_CRLF;
	case CRLF_TEXT_INPUT:
		return EOL_LF;
	case CRLF_UNDEFINED:
	case CRLF_AUTO_CRLF:
	case CRLF_AUTO_INPUT:
	case CRLF_TEXT:
	case CRLF_AUTO:
		/* fall through */
		return text_eol_is_crlf() ? EOL_CRLF : EOL_LF;
	}
	warning("Illegal crlf_action %d\n", (int)crlf_action);
	return core_eol;
}

static void check_safe_crlf(const char *path, enum crlf_action crlf_action,
                            struct text_stat *stats, enum safe_crlf checksafe)
{
