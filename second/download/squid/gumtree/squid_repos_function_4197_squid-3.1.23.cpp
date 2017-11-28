acl_arp_data *
aclParseArpData(const char *t)
{
    LOCAL_ARRAY(char, eth, 256);
    acl_arp_data *q = new acl_arp_data;
    debugs(28, 5, "aclParseArpData: " << t);

    if (sscanf(t, "%[0-9a-fA-F:]", eth) != 1) {
        debugs(28, 0, "aclParseArpData: Bad ethernet address: '" << t << "'");
        safe_free(q);
        return NULL;
    }

    if (!decode_eth(eth, q->eth)) {
        debugs(28, 0, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(28, 0, "aclParseArpData: Ignoring invalid ARP acl entry: can't parse '" << eth << "'");
        safe_free(q);
        return NULL;
    }

    return q;
}