static APR_INLINE ipaddr_chain *find_ipaddr(apr_sockaddr_t *sa)
{
    unsigned bucket;
    ipaddr_chain *trav;

    /* scan the hash apr_table_t for an exact match first */
    bucket = hash_addr(sa);
    for (trav = iphash_table[bucket]; trav; trav = trav->next) {
        server_addr_rec *sar = trav->sar;
        apr_sockaddr_t *cur = sar->host_addr;

        if (cur->port == 0 || sa->port == 0 || cur->port == sa->port) {
            if (apr_sockaddr_equal(cur, sa)) {
                return trav;
            }
        }    
    }
    return NULL;
}