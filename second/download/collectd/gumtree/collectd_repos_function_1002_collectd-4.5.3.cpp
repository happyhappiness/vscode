unsigned int
TC_NUM_RULES(const char *chain, TC_HANDLE_T *handle)
{
	struct chain_head *c;
	iptc_fn = TC_NUM_RULES;
	CHECK(*handle);

	c = iptcc_find_label(chain, *handle);
	if (!c) {
		errno = ENOENT;
		return (unsigned int)-1;
	}
	
	return c->num_rules;
}