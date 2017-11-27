static void submit6_chain( ip6tc_handle_t *handle, ip_chain_t *chain )
{
    const struct ip6t_entry *entry;
    int rule_num;

    /* Find first rule for chain and use the iterate macro */
    entry = ip6tc_first_rule( chain->chain, handle );
    if (entry == NULL)
    {
        DEBUG ("ip6tc_first_rule failed: %s", ip6tc_strerror (errno));
        return;
    }

    rule_num = 1;
    while (entry)
    {
        if (chain->rule_type == RTYPE_NUM)
        {
            submit6_match (NULL, entry, chain, rule_num);
        }
        else
        {
            IP6T_MATCH_ITERATE( entry, submit6_match, entry, chain, rule_num );
        }

        entry = ip6tc_next_rule( entry, handle );
        rule_num++;
    } /* while (entry) */
}