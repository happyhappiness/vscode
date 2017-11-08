void *util_ldap_search_node_copy(void *c)
{
    util_search_node_t *node = (util_search_node_t *)c;
    util_search_node_t *newnode = util_ald_alloc(sizeof(util_search_node_t));

    /* safety check */
    if (newnode) {

        /* copy vals */
        if (node->vals) {
            int k = 0;
            int i = 0;
            while (node->vals[k++]);
            if (!(newnode->vals = util_ald_alloc(sizeof(char *) * (k+1)))) {
                util_ldap_search_node_free(newnode);
                return NULL;
            }
            while (node->vals[i]) {
                if (!(newnode->vals[i] = util_ald_strdup(node->vals[i]))) {
                    util_ldap_search_node_free(newnode);
                    return NULL;
                }
                i++;
            }
        }
        else {
            newnode->vals = NULL;
        }
        if (!(newnode->username = util_ald_strdup(node->username)) ||
            !(newnode->dn = util_ald_strdup(node->dn)) ||
            !(newnode->bindpw = util_ald_strdup(node->bindpw)) ) {
            util_ldap_search_node_free(newnode);
            return NULL;
        }
        newnode->lastbind = node->lastbind;

    }
    return (void *)newnode;
}