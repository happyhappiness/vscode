static ipaddr_chain *find_default_server(apr_port_t port)
{
    server_addr_rec *sar;
    ipaddr_chain *trav = NULL;
    ipaddr_chain *wild_match = NULL;

    for (trav = default_list; trav; trav = trav->next) {
        sar = trav->sar;
        if (sar->host_port == port) {
            /* match! */
            return trav;
        }
        if (wild_match == NULL && sar->host_port == 0) {
            /* don't break, continue looking for an exact match */
            wild_match = trav;
        }
    }
    return wild_match;
}