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