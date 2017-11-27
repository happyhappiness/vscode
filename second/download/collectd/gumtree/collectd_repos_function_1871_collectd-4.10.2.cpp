int
TC_GET_REFERENCES(unsigned int *ref, const IPT_CHAINLABEL chain,
		  TC_HANDLE_T *handle)
{
	struct chain_head *c;

	iptc_fn = TC_GET_REFERENCES;
	if (!(c = iptcc_find_label(chain, *handle))) {
		errno = ENOENT;
		return 0;
	}

	*ref = c->references;

	return 1;
}