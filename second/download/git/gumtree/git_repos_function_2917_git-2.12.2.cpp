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