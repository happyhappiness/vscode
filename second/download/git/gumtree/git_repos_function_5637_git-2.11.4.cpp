static inline off_t pack_set_bytecount(struct pack_list *pl)
{
	off_t ret = 0;
	while (pl) {
		ret += pl->pack->pack_size;
		ret += pl->pack->index_size;
		pl = pl->next;
	}
	return ret;
}