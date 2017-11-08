void util_ldap_search_node_display(request_rec *r, util_ald_cache_t *cache, void *n)
{
    util_search_node_t *node = n;
    char date_str[APR_CTIME_LEN];

    apr_ctime(date_str, node->lastbind);

    ap_rprintf(r,
               "<tr valign='top'>"
               "<td nowrap>%s</td>"
               "<td nowrap>%s</td>"
               "<td nowrap>%s</td>"
               "</tr>",
               node->username,
               node->dn,
               date_str);
}