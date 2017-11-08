static int fsck_walk_tag(struct tag *tag, void *data, struct fsck_options *options)
{
	if (parse_tag(tag))
		return -1;
	return options->walk(tag->tagged, OBJ_ANY, data, options);
}