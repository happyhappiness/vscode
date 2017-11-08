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