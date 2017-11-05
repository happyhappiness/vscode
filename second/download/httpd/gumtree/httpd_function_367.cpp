void util_ldap_dn_compare_node_display(request_rec *r, util_ald_cache_t *cache, void *n)
{
    util_dn_compare_node_t *node = (util_dn_compare_node_t *)n;
    char *buf;

    buf = apr_psprintf(r->pool, 
             "<tr valign='top'>"
             "<td nowrap>%s</td>"
             "<td nowrap>%s</td>"
             "<tr>",
         node->reqdn,
         node->dn);

    ap_rputs(buf, r);
}