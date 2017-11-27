static int iptables_shutdown (void)
{
    int i;

    for (i = 0; i < chain_num; i++)
    {
	if ((chain_list[i] != NULL) && (chain_list[i]->rule_type == RTYPE_COMMENT))
	{
	    sfree (chain_list[i]->rule.comment);
	}
	sfree (chain_list[i]);
    }
    sfree (chain_list);

    return (0);
}