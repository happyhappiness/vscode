const char *
TC_GET_POLICY(const char *chain,
	      STRUCT_COUNTERS *counters,
	      TC_HANDLE_T *handle)
{
	struct chain_head *c;

	iptc_fn = TC_GET_POLICY;

	DEBUGP("called for chain %s\n", chain);

	c = iptcc_find_label(chain, *handle);
	if (!c) {
		errno = ENOENT;
		return NULL;
	}

	if (!iptcc_is_builtin(c))
		return NULL;

	*counters = c->counters;

	return standard_target_map(c->verdict);
}