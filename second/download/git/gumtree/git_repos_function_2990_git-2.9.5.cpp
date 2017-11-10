static struct rerere_id *new_rerere_id(unsigned char *sha1)
{
	return new_rerere_id_hex(sha1_to_hex(sha1));
}