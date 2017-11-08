void clear_shallow_info(struct shallow_info *info)
{
	free(info->ours);
	free(info->theirs);
}