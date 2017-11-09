static struct rerere_id *new_rerere_id_hex(char *hex)
{
	struct rerere_id *id = xmalloc(sizeof(*id));
	id->collection = find_rerere_dir(hex);
	id->variant = -1; /* not known yet */
	return id;
}