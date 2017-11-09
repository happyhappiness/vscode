static int process_tag(struct walker *walker, struct tag *tag)
{
	if (parse_tag(tag))
		return -1;
	return process(walker, tag->tagged);
}