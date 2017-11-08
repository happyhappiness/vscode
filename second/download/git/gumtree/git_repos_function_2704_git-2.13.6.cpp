void init_reflog_walk(struct reflog_walk_info **info)
{
	*info = xcalloc(1, sizeof(struct reflog_walk_info));
	(*info)->complete_reflogs.strdup_strings = 1;
}