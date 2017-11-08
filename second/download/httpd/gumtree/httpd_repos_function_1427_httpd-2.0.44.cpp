util_url_node_t *util_ald_create_caches(util_ldap_state_t *st, const char *url)
{
    util_url_node_t *curl = NULL;
    util_ald_cache_t *search_cache;
    util_ald_cache_t *compare_cache;
    util_ald_cache_t *dn_compare_cache;

    /* create the three caches */
    search_cache = util_ald_create_cache(st->search_cache_size,
					  util_ldap_search_node_hash,
					  util_ldap_search_node_compare,
					  util_ldap_search_node_copy,
					  util_ldap_search_node_free);
    compare_cache = util_ald_create_cache(st->compare_cache_size,
					   util_ldap_compare_node_hash,
					   util_ldap_compare_node_compare,
					   util_ldap_compare_node_copy,
					   util_ldap_compare_node_free);
    dn_compare_cache = util_ald_create_cache(st->compare_cache_size,
					      util_ldap_dn_compare_node_hash,
					      util_ldap_dn_compare_node_compare,
					      util_ldap_dn_compare_node_copy,
					      util_ldap_dn_compare_node_free);

    /* check that all the caches initialised successfully */
    if (search_cache && compare_cache && dn_compare_cache) {

        curl = (util_url_node_t *)apr_pcalloc(st->pool, sizeof(util_url_node_t));
        curl->url = url;
        curl->search_cache = search_cache;
        curl->compare_cache = compare_cache;
        curl->dn_compare_cache = dn_compare_cache;

        util_ald_cache_insert(util_ldap_cache, curl);

    }

    return curl;
}