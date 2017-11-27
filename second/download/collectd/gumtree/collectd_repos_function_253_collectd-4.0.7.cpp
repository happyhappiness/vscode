static int iptables_read (void)
{
    int i;
    static complain_t complaint;

    /* Init the iptc handle structure and query the correct table */    
    for (i = 0; i < chain_num; i++)
    {
	iptc_handle_t handle;
	ip_chain_t *chain;
	
	chain = chain_list[i];
	if (!chain)
	{
	    DEBUG ("chain == NULL");
	    continue;
	}

	handle = iptc_init( chain->table );
	if (!handle)
	{
	    DEBUG ("iptc_init (%s) failed: %s", chain->table, iptc_strerror (errno));
	    plugin_complain (LOG_ERR, &complaint, "iptc_init (%s) failed: %s",
		    chain->table, iptc_strerror (errno));
	    continue;
	}
	plugin_relief (LOG_INFO, &complaint, "iptc_init (%s) succeeded",
		chain->table);

	submit_chain (&handle, chain);
	iptc_free (&handle);
    }

    return (0);
}