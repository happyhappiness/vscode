void grep_source_clear(struct grep_source *gs)
{
	free(gs->name);
	gs->name = NULL;
	free(gs->path);
	gs->path = NULL;
	free(gs->identifier);
	gs->identifier = NULL;
	grep_source_clear_data(gs);
}