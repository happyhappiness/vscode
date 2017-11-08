static struct rerere_id *dirname_to_id(const char *name)
{
	static struct rerere_id id;
	strcpy(id.hex, name);
	return &id;
}