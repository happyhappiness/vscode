void init_notes_merge_options(struct notes_merge_options *o)
{
	memset(o, 0, sizeof(struct notes_merge_options));
	strbuf_init(&(o->commit_msg), 0);
	o->verbosity = NOTES_MERGE_VERBOSITY_DEFAULT;
}