static const unsigned char *rerere_dir_sha1(size_t i, void *table)
{
	struct rerere_dir **rr_dir = table;
	return rr_dir[i]->sha1;
}