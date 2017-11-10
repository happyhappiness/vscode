static int has_conforming_footer(struct strbuf *sb, struct strbuf *sob,
	int ignore_footer)
{
	struct trailer_info info;
	int i;
	int found_sob = 0, found_sob_last = 0;

	trailer_info_get(&info, sb->buf);

	if (info.trailer_start == info.trailer_end)
		return 0;

	for (i = 0; i < info.trailer_nr; i++)
		if (sob && !strncmp(info.trailers[i], sob->buf, sob->len)) {
			found_sob = 1;
			if (i == info.trailer_nr - 1)
				found_sob_last = 1;
		}

	trailer_info_release(&info);

	if (found_sob_last)
		return 3;
	if (found_sob)
		return 2;
	return 1;
}