static const char *rerere_id_hex(const struct rerere_id *id)
{
	return sha1_to_hex(id->collection->sha1);
}