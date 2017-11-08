static struct rerere_id *new_rerere_id_hex(char *hex)
{
	struct rerere_id *id = xmalloc(sizeof(*id));
	xsnprintf(id->hex, sizeof(id->hex), "%s", hex);
	return id;
}