static int freshen_packed_object(const unsigned char *sha1)
{
	struct pack_entry e;
	return find_pack_entry(sha1, &e) && freshen_file(e.p->pack_name);
}