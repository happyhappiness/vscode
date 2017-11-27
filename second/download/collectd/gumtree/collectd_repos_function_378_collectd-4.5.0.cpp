static int iptables_read (void)
{
    int i;
    int num_failures = 0;

    /* Init the iptc handle structure and query the correct table */    
    for (i = 0; i < chain_num; i++)
    {
	iptc_handle_t handle;
	ip_chain_t *chain;
	
	chain = chain_list[i];
	if (!chain)
	{
	    DEBUG ("iptables plugin: chain == NULL");
	    continue;
	}

	handle = iptc_init (chain->table);
	if (!handle)
	{
	    ERROR ("iptables plugin: iptc_init (%s) failed: %s",
		    chain->table, iptc_strerror (errno));
	    num_failures++;
	    continue;
	}

	submit_chain (&handle, chain);
	iptc_free (&handle);
    } /* for (i = 0 .. chain_num) */

    return ((num_failures < chain_num) ? 0 : -1);
}