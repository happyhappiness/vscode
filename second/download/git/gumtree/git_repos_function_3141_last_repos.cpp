const char *get_wt_convert_stats_ascii(const char *path)
{
	const char *ret = "";
	struct strbuf sb = STRBUF_INIT;
	if (strbuf_read_file(&sb, path, 0) >= 0)
		ret = gather_convert_stats_ascii(sb.buf, sb.len);
	strbuf_release(&sb);
	return ret;
}