static APR_INLINE ipaddr_chain *find_ipaddr(apr_sockaddr_t *sa)
{
    unsigned bucket;
    ipaddr_chain *trav = NULL;
    ipaddr_chain *wild_match = NULL;

    /* scan the hash table for an exact match first */
    bucket = hash_addr(sa);
    for (trav = iphash_table[bucket]; trav; trav = trav->next) {
        server_addr_rec *sar = trav->sar;
        apr_sockaddr_t *cur = sar->host_addr;

        if (cur->port == sa->port) {
            if (apr_sockaddr_equal(cur, sa)) {
                return trav;
            }
        }
        if (wild_match == NULL && (cur->port == 0 || sa->port == 0)) {
            if (apr_sockaddr_equal(cur, sa)) {
                /* don't break, continue looking for an exact match */
                wild_match = trav;
            }
        }
    }
    return wild_match;
}