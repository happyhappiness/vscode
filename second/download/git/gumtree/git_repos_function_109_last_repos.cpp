static void format_trailers(struct strbuf *sb, const char *msg)
{
	struct trailer_info info;

	trailer_info_get(&info, msg);
	strbuf_add(sb, info.trailer_start,
		   info.trailer_end - info.trailer_start);
	trailer_info_release(&info);
}