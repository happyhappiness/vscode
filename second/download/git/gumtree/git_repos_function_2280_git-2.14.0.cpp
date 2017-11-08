static int freshen_packed_object(const unsigned char *sha1)
{
	struct pack_entry e;
	if (!find_pack_entry(sha1, &e))
		return 0;
	if (e.p->freshened)
		return 1;
	if (!freshen_file(e.p->pack_name))
		return 0;
	e.p->freshened = 1;
	return 1;
}