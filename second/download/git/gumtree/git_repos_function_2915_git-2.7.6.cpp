static struct rerere_id *new_rerere_id_hex(char *hex)
{
	struct rerere_id *id = xmalloc(sizeof(*id));
	strcpy(id->hex, hex);
	return id;
}