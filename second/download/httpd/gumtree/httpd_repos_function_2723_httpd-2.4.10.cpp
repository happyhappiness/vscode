void util_ldap_compare_node_display(request_rec *r, util_ald_cache_t *cache, void *n)
{
    util_compare_node_t *node = n;
    char date_str[APR_CTIME_LEN];
    char *cmp_result;
    char *sub_groups_val;
    char *sub_groups_checked;

    apr_ctime(date_str, node->lastcompare);

    if (node->result == LDAP_COMPARE_TRUE) {
        cmp_result = "LDAP_COMPARE_TRUE";
    }
    else if (node->result == LDAP_COMPARE_FALSE) {
        cmp_result = "LDAP_COMPARE_FALSE";
    }
    else {
        cmp_result = apr_itoa(r->pool, node->result);
    }

    if(node->subgroupList) {
        sub_groups_val = "Yes";
    }
    else {
        sub_groups_val = "No";
    }

    if(node->sgl_processed) {
        sub_groups_checked = "Yes";
    }
    else {
        sub_groups_checked = "No";
    }

    ap_rprintf(r,
               "<tr valign='top'>"
               "<td nowrap>%s</td>"
               "<td nowrap>%s</td>"
               "<td nowrap>%s</td>"
               "<td nowrap>%s</td>"
               "<td nowrap>%s</td>"
               "<td nowrap>%s</td>"
               "<td nowrap>%s</td>"
               "</tr>",
               node->dn,
               node->attrib,
               node->value,
               date_str,
               cmp_result,
               sub_groups_val,
               sub_groups_checked);
}