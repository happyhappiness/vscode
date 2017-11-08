void grep_source_clear(struct grep_source *gs)
{
	FREE_AND_NULL(gs->name);
	FREE_AND_NULL(gs->path);
	FREE_AND_NULL(gs->identifier);
	grep_source_clear_data(gs);
}