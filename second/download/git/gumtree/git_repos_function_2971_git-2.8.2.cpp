static struct rerere_id *dirname_to_id(const char *name)
{
	static struct rerere_id id;
	xsnprintf(id.hex, sizeof(id.hex), "%s", name);
	return &id;
}