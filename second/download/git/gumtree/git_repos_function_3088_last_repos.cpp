void trailer_info_release(struct trailer_info *info)
{
	int i;
	for (i = 0; i < info->trailer_nr; i++)
		free(info->trailers[i]);
	free(info->trailers);
}