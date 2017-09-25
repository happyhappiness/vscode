    util_ald_free(cache, node->dn);
    util_ald_free(cache, node->attrib);
    util_ald_free(cache, node->value);
    util_ald_free(cache, node);
}

void util_ldap_compare_node_display(request_rec *r, util_ald_cache_t *cache, void *n)
{
    util_compare_node_t *node = (util_compare_node_t *)n;
    char date_str[APR_CTIME_LEN+1];
    char *buf, *cmp_result;

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

    buf = apr_psprintf(r->pool, 
             "<tr valign='top'>"
             "<td nowrap>%s</td>"
             "<td nowrap>%s</td>"
             "<td nowrap>%s</td>"
             "<td nowrap>%s</td>"
             "<td nowrap>%s</td>"
             "<tr>",
         node->dn,
         node->attrib,
         node->value,
         date_str,
         cmp_result);

    ap_rputs(buf, r);
}

/* ------------------------------------------------------------------ */

unsigned long util_ldap_dn_compare_node_hash(void *n)
{
    return util_ald_hash_string(1, ((util_dn_compare_node_t *)n)->reqdn);
}
