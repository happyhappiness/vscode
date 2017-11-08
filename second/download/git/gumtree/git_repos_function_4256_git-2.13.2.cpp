static int grep_source_is_binary(struct grep_source *gs)
{
	grep_source_load_driver(gs);
	if (gs->driver->binary != -1)
		return gs->driver->binary;

	if (!grep_source_load(gs))
		return buffer_is_binary(gs->buf, gs->size);

	return 0;
}