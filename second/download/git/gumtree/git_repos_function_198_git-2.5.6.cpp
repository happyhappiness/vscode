static char *pack_bitmap_filename(struct packed_git *p)
{
	char *idx_name;
	int len;

	len = strlen(p->pack_name) - strlen(".pack");
	idx_name = xmalloc(len + strlen(".bitmap") + 1);

	memcpy(idx_name, p->pack_name, len);
	memcpy(idx_name + len, ".bitmap", strlen(".bitmap") + 1);

	return idx_name;
}