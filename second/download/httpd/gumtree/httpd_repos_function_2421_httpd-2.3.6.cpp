void util_ldap_dn_compare_node_display(request_rec *r, util_ald_cache_t *cache, void *n)
{
    util_dn_compare_node_t *node = n;

    ap_rprintf(r,
               "<tr valign='top'>"
               "<td nowrap>%s</td>"
               "<td nowrap>%s</td>"
               "</tr>",
               node->reqdn,
               node->dn);
}