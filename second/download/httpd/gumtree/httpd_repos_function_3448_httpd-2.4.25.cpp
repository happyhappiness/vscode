void *util_ldap_search_node_copy(util_ald_cache_t *cache, void *c)
{
    util_search_node_t *node = c;
    util_search_node_t *newnode = util_ald_alloc(cache, sizeof *newnode);

    /* safety check */
    if (newnode) {

        /* copy vals */
        if (node->vals) {
            int k = node->numvals;
            int i = 0;
            if (!(newnode->vals = util_ald_alloc(cache, sizeof(char *) * (k+1)))) {
                util_ldap_search_node_free(cache, newnode);
                return NULL;
            }
            newnode->numvals = node->numvals;
            for (;k;k--) {
                if (node->vals[i]) {
                    if (!(newnode->vals[i] = util_ald_strdup(cache, node->vals[i]))) {
                        util_ldap_search_node_free(cache, newnode);
                        return NULL;
                    }
                }
                else
                    newnode->vals[i] = NULL;
                i++;
            }
        }
        else {
            newnode->vals = NULL;
        }
        if (!(newnode->username = util_ald_strdup(cache, node->username)) ||
            !(newnode->dn = util_ald_strdup(cache, node->dn)) ) {
            util_ldap_search_node_free(cache, newnode);
            return NULL;
        }
        if (node->bindpw) {
            if (!(newnode->bindpw = util_ald_strdup(cache, node->bindpw))) {
                util_ldap_search_node_free(cache, newnode);
                return NULL;
            }
        } else {
            newnode->bindpw = NULL;
        }
        newnode->lastbind = node->lastbind;

    }
    return (void *)newnode;
}