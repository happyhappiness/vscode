static int submit_match (const struct ipt_entry_match *match,
		const struct ipt_entry *entry,
		const ip_chain_t *chain,
		int rule_num) 
{
    int status;
    value_t values[1];
    value_list_t vl = VALUE_LIST_INIT;

    /* Select the rules to collect */
    if (chain->rule_type == RTYPE_NUM)
    {
	if (chain->rule.num != rule_num)
	    return (0);
    }
    else
    {
	if (strcmp (match->u.user.name, "comment") != 0)
	    return (0);
	if ((chain->rule_type == RTYPE_COMMENT)
		&& (strcmp (chain->rule.comment, (char *) match->data) != 0))
	    return (0);
    }

    vl.values = values;
    vl.values_len = 1;
    vl.time = time (NULL);
    sstrncpy (vl.host, hostname_g, sizeof (vl.host));
    sstrncpy (vl.plugin, "iptables", sizeof (vl.plugin));

    status = snprintf (vl.plugin_instance, sizeof (vl.plugin_instance),
	    "%s-%s", chain->table, chain->chain);
    if ((status < 1) || ((unsigned int)status >= sizeof (vl.plugin_instance)))
	return (0);

    if (chain->name[0] != '\0')
    {
	strncpy (vl.type_instance, chain->name, sizeof (vl.type_instance));
    }
    else
    {
	if (chain->rule_type == RTYPE_NUM)
	    snprintf (vl.type_instance, sizeof (vl.type_instance),
		    "%i", chain->rule.num);
	else
	    strncpy (vl.type_instance, (char *) match->data,
		    sizeof (vl.type_instance));
    }
    vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';

    values[0].counter = (counter_t) entry->counters.bcnt;
    plugin_dispatch_values ("ipt_bytes", &vl);

    values[0].counter = (counter_t) entry->counters.pcnt;
    plugin_dispatch_values ("ipt_packets", &vl);

    return (0);
}