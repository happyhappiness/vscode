static void clear_push_info(void *util, const char *string)
{
	struct push_info *info = util;
	free(info->dest);
	free(info);
}