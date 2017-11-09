int reflog_walk_empty(struct reflog_walk_info *info)
{
	return !info || !info->nr;
}