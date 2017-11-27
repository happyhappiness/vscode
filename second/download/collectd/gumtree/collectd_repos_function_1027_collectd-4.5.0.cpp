int
TC_SET_POLICY(const IPT_CHAINLABEL chain,
	      const IPT_CHAINLABEL policy,
	      STRUCT_COUNTERS *counters,
	      TC_HANDLE_T *handle)
{
	struct chain_head *c;

	iptc_fn = TC_SET_POLICY;

	if (!(c = iptcc_find_label(chain, *handle))) {
		DEBUGP("cannot find chain `%s'\n", chain);
		errno = ENOENT;
		return 0;
	}

	if (!iptcc_is_builtin(c)) {
		DEBUGP("cannot set policy of userdefinedchain `%s'\n", chain);
		errno = ENOENT;
		return 0;
	}

	if (strcmp(policy, LABEL_ACCEPT) == 0)
		c->verdict = -NF_ACCEPT - 1;
	else if (strcmp(policy, LABEL_DROP) == 0)
		c->verdict = -NF_DROP - 1;
	else {
		errno = EINVAL;
		return 0;
	}

	if (counters) {
		/* set byte and packet counters */
		memcpy(&c->counters, counters, sizeof(STRUCT_COUNTERS));
		c->counter_map.maptype = COUNTER_MAP_SET;
	} else {
		c->counter_map.maptype = COUNTER_MAP_NOMAP;
	}

	set_changed(*handle);

	return 1;
}