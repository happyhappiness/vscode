static ipaddr_chain *find_default_server(apr_port_t port)
{
    server_addr_rec *sar;
    ipaddr_chain *trav;

    for (trav = default_list; trav; trav = trav->next) {
        sar = trav->sar;
        if (sar->host_port == 0 || sar->host_port == port) {
            /* match! */
            return trav;
        }
    }
    return NULL;
}